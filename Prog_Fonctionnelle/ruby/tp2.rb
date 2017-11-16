#  ============================================================================
#  Examples of classes using Ruby --- January 2017

class Animal
  #
  attr_reader :name
  #
  def initialize(name_0)
    @name = name_0   #  "@...":  instance variable,
    @@animalnb += 1  #  "@@...": static   .........
  end
  #
  def eat
    puts 'I\'m eating.'
  end
  #
  @@animalnb = 0
  #
  def self.nb
    @@animalnb
  end
  #
  CrDate = '2016/12/13'
  #
end

class Dog < Animal
  #
  attr_reader :ownername
  #
  def initialize(name_0,ownername_0)
    super(name_0)
    @ownername = ownername_0
  end
  #
  def bark
    puts 'I\'m barking.'
  end
  #
  class << self
    undef_method :nb
  end
  #
end

class Monkey < Animal
  #
  def climb
    puts 'I\'m climbing.'
  end
  #
  class << self
    undef_method :nb
  end
  #
end

#  "$<variable-name>": global variable.
$a = Animal.new('Baloo')
$a.eat
p $a.name

$d = Dog.new('Rintintin','Bonanza')
$d.eat
$d.bark
p $d.name
p $d.ownername

$m = Monkey.new('Snow Flake')
$m.eat
$m.climb
p $m.name

p Animal.nb

$kingkong = Monkey.new('King-Kong')

def $kingkong.skullisland
  puts 'I\'m at home.'
end

class << $kingkong
  #
  def empirestatebuilding
    puts 'That\'s the end, my friend.'
  end
  #
end

class Dog
  #
  def bite
    puts 'Biting U!'
  end
  #
  def do_with_names_and(x)
    yield(@name,@ownername,x)
  end
  #
end

$d.bite

puts Animal::CrDate

class Animal
  #
  def gimme
    puts 'Gimme, gimme ' + yield
  end
  #
  def do_with_name
    puts "I'm #{@name}"
    yield(@name) if block_given?
  end
  #
end

class Fixnum

  def fact
    if self >= 0
      (1..self).inject(1) do |already,next_n| already * next_n end
    else
      nil
    end
  end

end

class Array

  def halfapply
    result = []
    each_with_index do |x, index| result.push(yield(x)) if index.even? end
    result
  end

  def halfapply_v2
    result = []
    each_index do |index| result.push(yield(at(index))) if index.even? end
    result
  end

  def halfapply_v3
    result = Array.new(length.fdiv(2).ceil)
    forward_index = 0
    each_index do |index|
      if index.even?
        result[forward_index] = yield(at(index))
        forward_index += 1
      end
    end
    result
  end
end

class Animal
  def with(a)
    if self.class == a.class
      puts "#{@name} with #{a.name} for #{yield}"
      true
    else
      false
    end
  end
end

class Quadrilateral
  attr_reader\
    : length_0,:length_1,:length_2,:length_3,:angle_0,:angle_1,:angle_2

  def initialize(l0,l1,l2,l3,a0,a1,a2)
    @length_0 = l0
    @length_1 = l1
    @length_2 = l2
    @length_3 = l3
    @angle_0 = a0
    @angle_1 = a1
    @angle_2 = a2
  end

  def perimeter
    @length_0 + @length_1 + @length_2 + @length_3
  end

  def surface
    nil
  end
end

class Parrallelogramme < Quadrilateral
  undef_method\
    : length_2,:length_3,:angle_1,:angle_2

  def initialize(l0,l1,a0)
    super(l0,l1,l0,l1,a0,Math::PI - a0,a0)
  end

  def perimeter
    2 *(@length_0 + @length_1)
  end

  def surface
    @length_0 * @length_1 * Math::cos(@angle_0 - Math::PI / 2.0)
  end
end

class Rectangle < Parrallelogramme
  undef_method\
    : angle_0

  def initialize(l0,l1)
    super(l0,l1,Math::PI / 2.0)
  end

  def surface
    @length_0 * @length_1
  end
end

class Carre < Rectangle
  undef_method\
    : length_1

  def initialize(l0)
    super(l0,l0)
  end

  def perimeter
    4 * @length_0
  end
end

module Perimetre_Losange
  def perimettre
    puts "I'm a #{self.class}, yeah!" if $debug
    4 * @length_0
  end
end


def filtermap(a, regexp)
  result = []
  a.each do |x| result.push(yield(x)) if ... end
end
