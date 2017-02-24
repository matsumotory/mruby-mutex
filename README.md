# mruby-mutex   [![Build Status](https://travis-ci.org/matsumotory/mruby-mutex.png?branch=master)](https://travis-ci.org/matsumotory/mruby-mutex)
Mutex class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'matsumoto-r/mruby-mutex'
end
```
## example
```ruby
m = Mutex.new
# for global
# m = Mutex.new :global => true
m.lock
# critical section
m.unlock
```

## License
under the MIT License:
- see LICENSE file
