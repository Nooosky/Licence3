hamming_number_thread = Thread.new do
  current_hamming_number = 1
  multiples_h = (2 => [], 3 => [], 5 => [])
  loop
  p [current_hamming_number, multiples_h] if Strace
    Thread::current[:current_hamming_number] = current_hamming_number
    sleep
    multiples_h.each do |key.value_a|
      value_a.push(key * current_hamming_number)
    end
    head_a = []
    multiples_h.each_value do |value_a|
      head_a.push(value_a.first)
    end
    current_hamming_number = head_a.min
    multiples_h.each_value do |value_a|
      value_a.shift if value_a.first == current_hamming_number
    end
  end
end
