#to integer

' 273.15 '.to_i
#=> 273

a = [23, 11, 2017]
a.sort
#=> Array not edited

a.sort!
#=> Array edited

1 <=> 2
#=> -1

2 <=> 1
#=> 1

1 <=> 1
#=> 0
# <=> useful for descending sort

a.sort do |x, y| - (x <=> y) end
#=> descending sort

#  \A\s*(?:\+|-)?[0-9]+(?:\ [0-9]+)?\s*\z

def sort_both_fixnum_string(a0)
  a0.sort do |x0, x1|
    if x0.class == Fixnum or x0 =~ /\A\s*(?:\+|-)?[0-9]+(?:\.[0-9]+)?\s*\z/
      if x1.class == Fixnum or x1 =~ /\A\s*(?:\+|-)?[0-9]+(?:\.[0-9]+)?\s*\z/
        x0.to_i <=> x1.to_i
      else
        -1
      end
    elsif x1.class == Fixnum or x1 =~ /\A\s*(?:\+|-)?[0-9]+(?:\.[0-9]+)?\s*\z/
      1
    else
      x0 <=> x1
    end
  end
end

def sort_both_fixnum_string_v2(a0)
  touch =
    Proc.new do |x|
      x.class == Fixnum or x =~ /\A\s*(?:\+|-)?[0-9]+(?:\.[0-9]+)?\s*\z/
    end
  a0.sort do |x0, x1|
    touch_x0 = touch(x0)
    touch_x1 = touch(x1)
    touch_x0 ? (touch_x1 ? x0.to_i <=> x1.to_i : -1) : touch_x1 ? 1 : x0 <=> x1
  end
end
