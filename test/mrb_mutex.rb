##
## Mutex Test
##

assert("Mutex#hello") do
  t = Mutex.new "hello"
  assert_equal("hello", t.hello)
end

assert("Mutex#bye") do
  t = Mutex.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Mutex.hi") do
  assert_equal("hi!!", Mutex.hi)
end
