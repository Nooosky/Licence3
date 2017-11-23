#  ============================================================================
#
#            Definitions for Lab Class #7
#
#  ============================================================================
#
#  Author: J.-M. Hufflen
#  Date: November 2017
#
#  ============================================================================

#  Total size of a directory's contents

class File
  #
  def self.whole_size(path)
    if File.directory?(path)
      size_accumulator = 0
      Dir.glob(File.join(path,'**','*')) do |path_0|
        size_accumulator += File.size(path_0) if File.file?(path_0)
      end
      size_accumulator
    else
      File.size(path)
    end
  end
  #
end

#  Testing exceptions

def testexceptions(s)
  begin
    begin
      eval s
    rescue ZeroDivisionError
      p 0
      1
    else
      p 2
      3
    ensure
      p 4
      5
    end
  rescue StandardError => e
    p e.message
    p 6
    7
  else
    p 8
    9
  ensure
    p 10
    11
  end
end

p(testexceptions('2017'))
p(testexceptions('1/0'))
p(testexceptions "open('nonexistingfile')")

def testexceptionsv2
  begin
    begin
      yield
    rescue ZeroDivisionError
      p 0
      1
    else
      p 2
      3
    ensure
      p 4
      5
    end
  rescue StandardError => e
    p e.message
    p 6
    7
  else
    p 8
    9
  ensure
    p 10
    11
  end
end

p(testexceptionsv2 do p 'OK'
  2017
end)

p(testexceptionsv2 do p 'Division by zero'
  1 / 0
end)

p(testexceptionsv2 do p 'Opening file failed'
  open 'nonexistingfile'
end)

#  Removing accents from strings

class String
  #
  ACCENTED_LETTER_MAPPING = { 
    'A' => [192,193,194,195,196,197],'C' => [199],'E' => [200,201,202,203],
    'I' => [204,205,206,207],'N' => [209],'O' => [210,211,212,213,214,216],
    'U' => [217,218,219,220],'Y' => [221],'a' => [224,225,226,227,228,229,230],
    'c' => [231],'e' => [232,233,234,235],'i' => [236,237,238,239],
    'n' => [241],'o' => [242,243,244,245,246,248],'u' => [249,250,251,252],
    'y' => [253,255],'AE' => [306],'ae' => [346],'OE' => [188],'oe' => [189]
  }
  #
  def removeaccents    
    str = String.new(self)
    String::ACCENTED_LETTER_MAPPING.each do |letter,accents|
      packed = accents.pack('U*')
      rxp = Regexp.new("[#{packed}]",nil)
      str.gsub!(rxp,letter)
    end
    str
  end
  # 
end
