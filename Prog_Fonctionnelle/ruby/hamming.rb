hamming_number_thread = Thread.new do
  current_hamming_number = 1
  multiples_h = (2 => [], 3 => [], 5 => [])
  loop
    Thread::current[:current_hamming_number] = current_hamming_number
    sleep
    multiples_h.each do |key.value_a|
      ** multiplier par la clef et mettre en queue de chaque tableau **
    end
    head_a = []
    multiples_h.each_value do |value_a|
      ** recuperer les elements de tete sans les enlever **
    end
    current_hamming_number = head_a.min
    multiples_h.each_value do |value_a|
      **virer le minimum chaque fois qu'on le trouve en tete **
    end
  end
end
