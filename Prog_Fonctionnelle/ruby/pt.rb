def iterate(n,x)
  res=x
  n.times do
    res=yield(res)
  end
  res
end


class Array
  def included_into?(a0)
    self.all? { |elem| a0.include? elem }
  end

  def same_elements_than?(a0)
    self.included_into?(a0) and a0.included_into?(self)
  end

end

def derive_wrt(x, y)
  (yield(x + h) - yield(x))/h
end

def prefix_of?(a0)
  if length <= a0.length
    each_index do |index| return false unless at(index) == a0(index) end
      true
  else
    false
  end
end

def partition(flag)
  left = []
  right = []
  if flag
    each do |x| yield(x) ? left.push(x) : right.push(x) end
  else
    each do |x| yield(x) ? left.unshift(x) : right.unshift(x) end
  end
  [left, right]
end

def surround
  result = []
  each do |x| yield(x) ? result.push((x)) : result.push(x) end
  result
end

def calculation(a, b)
  yield(a, b)
end

puts calculation(5, 6) { |a, b| a + b } # addition
puts calculation(5, 6) { |a, b| a - b } # subtraction

a + ..
a.concat

a.first
a.shift

a.last
a.pop

a0 * 2


noms=["Charles", "Karim", "Abdelkader", "Timmy"]

def fun_test(noms)
        noms.each do |noms|
                yield noms
        end
end

fun_test(noms) do |nom|
        puts ("Bonjour " + nom + " pret pour le vietnam ?")
end

def fun_test(noms)
        noms.each do |nom|
                p ("Wesh " +nom+ " bien rebeu ?")
        end
        return true
end

a = [0,1,2,3]
a[-1] // 3

a.reverse_each do |x| p x end
3
2
1
0

class Array
    #

    def right_inject(init)
      result = init
      reverse_each do |x| result = yield(x, result) end
      result
    end

    #
    [1,2,3,4].right_inject(2018) do |x,y| x - y end

    def right_inject_v2(init)
    # with negative index, yeah!
      result = init
      -1.downto(- length) do |backward_index|
        result = yield(at(backward_index), result)
      end
      result
    end
end


[abc] 	A single character of: a, b, or c
[^abc] 	Any single character except: a, b, or c
[a-z] 	Any single character in the range a-z
[a-zA-Z] 	Any single character in the range a-z or A-Z
^ 	Start of line
$ 	End of line
\A 	Start of string
\z 	End of string
. 	Any single character
\s 	Any whitespace character
\S 	Any non-whitespace character
\d 	Any digit
\D 	Any non-digit
\w 	Any word character (letter, number, underscore)
\W 	Any non-word character
\b 	Any word boundary
(...) 	Capture everything enclosed
(a|b) 	a or b
a? 	Zero or one of a
a* 	Zero or more of a
a+ 	One or more of a
a{3} 	Exactly 3 of a
a{3,} 	3 or more of a
a{3,6} 	Between 3 and 6 of a
