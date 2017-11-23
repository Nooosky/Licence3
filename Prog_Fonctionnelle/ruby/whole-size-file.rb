#  ============================================================================
#
#            Patch for directories' sizes
#
#  ============================================================================
#
#  Author: J.-M. Hufflen
#  Date: January 2017
#
#  ============================================================================

class File
  #
  def self.whole_size(path)
    size_accumulator = 0
    Dir.glob(File.join(path,'**','*')) do |path_0|
      size_accumulator += File.size(path_0) if File.file?(path_0)
    end
    size_accumulator
  end
  #
end
