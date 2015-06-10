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

