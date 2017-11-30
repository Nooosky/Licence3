#load 'for-lc-7.rb'


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

require 'find'

def look_4_pdf_files(path)
  pdf_files_a = []
  Find.find(path) do |path_0| pdf_files_a.push(path_0) if path_0 =~ /\.pdf\z/
  end
  pdf_files_a
end

def sort_by_path(path)
  dir_a = []
  Find.find(path) do |path_0| dir_a.push(path_0) if File.directory?(path_0) end
  dir_a.sort! do |dir_0, dir_1|
    File.whole_size(dir_0) <=> File.whole_size(dir_1)
end


def sort_by_path_v2(path)
  h = {}
  Find.find(path) do |path_0|
    h[path_0] = File.whole_size(path_0) if File.directory?(path_0)
  end
  (h.sort do |pair_0, pair_1|
    pair_0[1] <=> pair_1[1]
  end).
    map do |pair|
      pair[0]
    end
  end
end

class OutOfBounds < Exception
end

class Array
  #
  def protected_i(index)
    if (-length...length) === index
      at(index)
    else
      raise OutOfBounds
    end
  end
end

def outofboundsnb(a, index_a)
  result = 0
  index_a.each do |index|
    begin
      a.protected_i(index)
    rescue OutOfBounds
      result += 1
    end
  end
  result
end
end
