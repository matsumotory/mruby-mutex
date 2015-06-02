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
