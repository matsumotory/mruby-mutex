/*
** mrb_mutex.c - Mutex class
**
** Copyright (c) MATSUMOTO Ryosuke 2015
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_mutex.h"
#include <sys/shm.h>
#include <pthread.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

pthread_mutex_t mm = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
  pthread_mutex_t *mutex;
  pthread_mutexattr_t mutex_attr;
  int shmid;
  unsigned int global:1;
} mrb_mutex_data;

static void mrb_mutex_data_free(mrb_state *mrb, void *p)
{
  mrb_mutex_data *data = p;

  if (data->global) {
    if (shmctl(data->shmid, IPC_RMID, NULL) != 0) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "shctl failed");
    }
    shmdt(data->mutex);
  }
  pthread_mutex_destroy(data->mutex);
  mrb_free(mrb, data);
}


static const struct mrb_data_type mrb_mutex_data_type = {
  "mrb_mutex_data", mrb_mutex_data_free,
};

static mrb_value mrb_mutex_init(mrb_state *mrb, mrb_value self)
{
  mrb_mutex_data *data;
  pthread_mutex_t *m = NULL;
  pthread_mutexattr_t mat;
  int shmid;
  unsigned int global = 0;

  mrb_get_args(mrb, "|b", &global);

  data = (mrb_mutex_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_mutex_data_type;
  DATA_PTR(self) = NULL;
  data = (mrb_mutex_data *)mrb_malloc(mrb, sizeof(mrb_mutex_data));

  if (global) {
    shmid = shmget(IPC_PRIVATE, sizeof(pthread_mutex_t), 0600);
    if (shmid < 0) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "shmget failed");
    }

    m = shmat(shmid, NULL, 0);
    if ((int)m == -1) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "shmat failed");
    }

    pthread_mutexattr_init(&mat);

    if (pthread_mutexattr_setpshared(&mat, PTHREAD_PROCESS_SHARED) != 0) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "pthread_mutexattr_setpshared failed");
    }

    pthread_mutex_init(m, &mat);
  } else {
    shmid = -1;
    pthread_mutex_init(&mm, NULL);
    m = &mm;
  }

  data->mutex = m;
  data->mutex_attr = mat;
  data->shmid = shmid;
  data->global = global;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_mutex_lock(mrb_state *mrb, mrb_value self)
{
  mrb_mutex_data *data = DATA_PTR(self);

  if (pthread_mutex_lock(data->mutex)  != 0) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "pthread_mutex_lock failed");
  }

  return mrb_fixnum_value(0);
}

static mrb_value mrb_mutex_unlock(mrb_state *mrb, mrb_value self)
{
  mrb_mutex_data *data = DATA_PTR(self);

  if (pthread_mutex_unlock(data->mutex)  != 0) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "pthread_mutex_unlock failed");
  }

  return mrb_fixnum_value(0);
}

void mrb_mruby_mutex_gem_init(mrb_state *mrb)
{
    struct RClass *mutex;
    mutex = mrb_define_class(mrb, "Mutex", mrb->object_class);
    mrb_define_method(mrb, mutex, "new2", mrb_mutex_init, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, mutex, "lock", mrb_mutex_lock, MRB_ARGS_NONE());
    mrb_define_method(mrb, mutex, "unlock", mrb_mutex_unlock, MRB_ARGS_NONE());
    DONE;
}

void mrb_mruby_mutex_gem_final(mrb_state *mrb)
{
}

