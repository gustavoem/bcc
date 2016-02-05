def yield_read
    get_number {|x| @a = x}
    get_number {|x| @b = x}
    puts "a = #{@a} #{@b}"
end

def get_number
    yield 1
end

yield_read
