MRuby::Gem::Specification.new('mruby-mutex') do |spec|
  spec.license = 'MIT'
  spec.authors = 'MATSUMOTO Ryosuke'
  if RUBY_PLATFORM =~ /darwin/i
    spec.linker.libraries << ['pthread']
  else
    spec.linker.libraries << ['pthread', 'rt']
  end
end
