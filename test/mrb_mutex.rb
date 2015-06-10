##
## Mutex Test
##

assert("Mutex#lock") do
  t = Mutex.new
  assert_equal(0, t.lock)
  t.unlock
end

assert("Mutex#unclock") do
  t = Mutex.new
  t.lock
  assert_equal(0, t.unlock)
end

assert("Mutex(:global => true)#lock") do
  t = Mutex.new :global => true
  assert_equal(0, t.lock)
  t.unlock
end

assert("Mutex(:global => true)#unclock") do
  t = Mutex.new :global => true
  t.lock
  assert_equal(0, t.unlock)
end

assert("Mutex#try_lock") do
  t = Mutex.new
  assert_equal(true, t.try_lock)
  t.unlock
end

assert("Mutex#try_lock_loop") do
  t = Mutex.new
  t.lock
  loop_locked = false
  # try_lock_loop test: waiting timeout 5sec by default
  t.try_lock_loop do
    loop_locked = true
  end
  assert_equal(true, loop_locked)
  t.unlock
end

