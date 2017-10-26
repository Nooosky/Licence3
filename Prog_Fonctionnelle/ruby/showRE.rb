def showRE(target,regexp)
  #  Highlights with chevrons where match occurs.
  p "#{$`}>>>>#{$&}<<<<#{$'}" if target =~ regexp
end

p showRE('beginning <a>Try 1</a><a>Try 2</a> ending',/<a>.*<\/a>/)
p showRE('beginning <a>Try 1</a><a>Try 2</a> ending',/<a>.*?<\/a>/)

p showRE('beginning!nning!nning!nningending',/(.*)!\1/)
p showRE('beginning!nning!nning!nningending',/(.*?)!\1/)

p 'Little players!'.sub(/little/,'master')
p 'Little players!'.sub(/little/i,'master')

$s = 'beginning <a>Try 1</a><a>Try 2</a> ending'
p $s.sub(/(<a>.*?<\/a>)(<a>.*?<\/a>)/,'\2\1')
p $s
p $s.sub!(/(<a>.*?<\/a>)(<a>.*?<\/a>)/,'\2\1')
p $s
$r = /(<a>(?:.*?)<\/a>)*/
p $r.class
p $s.gsub($r,'<b>\1</b>')
$r0 = /<a>(.*?)<\/a>/
p $s.gsub($r0,'<b>\1</b>')

p /<a>.*<\/a>/.match($s)
p /<a>.*?<\/a>/.match($s)

m = /<a>(.*?)<\/a><a>(.*?)<\/a>/.match($s)
p m

for i in 0..2
  p m[i]
  p m.begin(i)
  p m.end(i)
end

p m.post_match
m0 = $r.match($s)
p m0
m1 = $r0.match($s)
p m1

# fonction pour le nombre de bit
class Fixnum
  def bit_length
    zero? ? 1 : Math.log(self + 1,2).ceil
  end
end

def fibonacci(n)
  left = 0
  right = 1
  counter = 0
  while counter < n
    left,right = right,left + right
    counter += 1
  end
  right
end

# ?: pour ne pas memoriser
def match_french_departement_number(s)
  (s =~ /\A(?:0[1-9]|[13-8][0-9]|2[AB1-9]|9(?:[0-5]|7[1-46]))\z/) == 0
end
