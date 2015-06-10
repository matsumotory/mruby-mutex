MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem '../mruby-mutex'
  conf.gem :github => 'matsumoto-r/mruby-sleep'
end
