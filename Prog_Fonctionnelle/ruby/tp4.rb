#load 'for-lc-7.rb'
require 'find'


def superscan(path)
  unsaved_a = [] #[".....", ...]
  remaining_a = [] #[[".....", "...."], ...]
  #                    ^old name  ^new name
  Find.find(path) do |path_0|
    if File.directory?(path_0)

    end
  end
end
