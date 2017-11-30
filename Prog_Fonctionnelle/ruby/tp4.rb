#load 'for-lc-7.rb'
require 'find'

$s_regexp = /\s/

def superscan(path)
  unsaved_a = [] #[".....", ...]
  remaining_a = [] #[[".....", "...."], ...]
  #                    ^old name  ^new name
  Find.find(path) do |path_0|
    if File.directory?(path_0)
      if path_0.length > 200
        unsaved_a.push(path_0)
      else
        the_dirname, the_basename = File.split(path_0)
        unless the_basename.ascii_only? and the_dirname !~ $s_regexp
          basename_0 = the_basename.removeaccents.gsub($s_regexp, '_')
          basename_1 = basename_0
          nb_4_suffix = 1
          while File.exist?(path_1 = File.join(the_dirname, basename_1))
            basename_1 = "#{basename_0}-#{nb_4_suffix}"
            nb_4_suffix += 1
          end
          remaining_a.push([path_0, path_1])
        end
      end
    end
  end
  unsaved_a + remaining_a
end


def superscan_v2(path)
  unsaved_a = []
  renamed_a = []
  remaining_a = []
<<<<<<< HEAD
  exists_or_about =
    Proc.new do |path_0|
      File.exist?(path_0) or renamed_a.find do |path_1| path_1 == path_0 end
      end
=======
  exist_or_about =
    Proc.new do |path_0|
      File.exists?(path_0) or renamed_a.find do |path_1| path_1 == path_0 end
    end
>>>>>>> 71afab5c440a581b3263ceb0014d6da7fdead15b

  Find.find(path) do |path_0|
    if File.directory?(path_0)
      if path_0.length > 200
        unsaved_a.push(path_0)
      else
        the_dirname, the_basename = File.split(path_0)
        unless the_basename.ascii_only? and the_dirname !~ $s_regexp
          basename_0 = the_basename.removeaccents.gsub($s_regexp, '_')
          basename_1 = basename_0
          nb_4_suffix = 1
          while exists_or_about[path_1 = File.join(the_dirname, basename_1)]
            basename_1 = "#{basename_0}-#{nb_4_suffix}"
            nb_4_suffix += 1
          end
          renamed_a.push(path_1)
          remaining_a.push([path_0, path_1])
        end
      end
    end
  end
  unsaved_a + remaining_a
end
