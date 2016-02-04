class Dessert
  attr_accessor :name
  attr_accessor :calories

  def initialize(name, calories)
    @name = name
    @calories = calories
  end

  def healthy?
    @calories < 200
  end

  def delicious?
    true
  end

end

class JellyBean < Dessert
  attr_accessor :flavor
  
  def initialize(flavor)
    @flavor = flavor
    @name = flavor + " jelly bean"
    @calories = 5
  end

  def delicious?
      if @flavor != "licorice"
          true
      else
          false
      end
  end
end
