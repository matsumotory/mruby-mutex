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

  def try_lock_loop retrytime = 100000, timeout = 500000 * 10, &b
    count = 0
    self_unlock = false
    loop do
      count += 1
      if self.try_lock
        instance_eval &b
        break
      elsif timeout < retrytime * count
        self.unlock
        self_unlock = true
      else
        usleep retrytime
      end
    end
    self_unlock
  end
end
