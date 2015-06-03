class Mutex
  def initialize obj = nil
    unless obj.nil?
      if obj[:global] == true || obj[:global] == false
        self.new2 obj[:global]
      else
        raise ":global => true or false"
      end
    else
      self.new2
    end
  end
end
