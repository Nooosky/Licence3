hamming_number_thread = Thread.new do
  current_hamming_number = 1
  multiples_h = (2 => [], 3 => [], 5 => [])
  loop
    Thread::current[:current_hamming_number] = current_hamming_number
    sleep
    
