def reverse_iterate_a(n,x)
    resultat = []
    if n != 0
        n.times do
            x = yield(x)
            resultat.insert(0,x)
        end
    end
    resultat
end

reverse_iterate_a(0,2017) do |x| x + 1 end
reverse_iterate_a(10,2017) do |x| x + 1 end

class Array
  def suffix_of?(a0)
    if length <= a0.length
      each_index do |index|
        if !(at(length - index) == a0(length - index))
          false
        end
      end
        true
    else
      false
    end
  end

  def involutory_elements
    resultat = []
    x = yield(x)
    resultat.insert(0,x)
  end

  def stamning
    resultat = []
    each_index do |index| (index + 1).times do resultat.push(at(index)) end end
    resultat
  end
end

[7,12,2017].suffix_of?([12,2017])
[7,12,2017].suffix_of?([2001,7,12,2017])

[true, 2017, false, nil].involutory_elements do |x| not x end

[7,12,2017].stamning

class Hash
  def reciprocal(value0)
    resultat = []
    each do |key, value|
      if value == value0
        resultat.push(key)
      end
    end
    resultat
  end

  def occurence_nbs

  end
end

$h = {1 => 2, 3 => 4, 4 => 2, 5 => 6}
$h.reciprocal(1)
$h.reciprocal(2)
$h.reciprocal(4)

$h.occurence_nbs


def match_french_number_plate(s)
  letters = '([A-Z][A-Z]&[^(FN|KK|PQ|PT|QQ|SS|WC)])'
  digits = '([0-9][0-9][0-9]|[^(000)])'
  tiret = '(-)'

  (s=~ Regexp.new('\\A' + letters + tiret + digits + tiret + letters + '\\z')) == 0
end

match_french_number_plate('CK-777-SJ')
match_french_number_plate('CK-110-NZ')
match_french_number_plate('CK-789-KJ')
match_french_number_plate('AG-666-PT')
