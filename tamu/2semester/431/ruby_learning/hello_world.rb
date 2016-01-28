BEGIN{
    puts "We can use begin to run before everything"
}

def hello_speaker
    phrase = "Hello World" 
    puts phrase
end

hello_speaker
puts `echo Im calling echo`



#inline comment
=begin
     these are allll comments
     free to comment
=end
