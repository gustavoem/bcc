module FunWithStrings
  def palindrome?
    s = self.downcase.gsub(/\W+/, "")
    s == s.reverse
  end

  def count_words
    v = self.downcase.split(/\W+/).reject{|s| s.empty?}
    hash = {}
    v.each{|x| 
        if hash.has_key?(x)
            hash[x] = hash[x] + 1
        else
            hash[x] = 1
        end
    }
    hash
  end

  def anagram_groups
    # your code here
  end

end

# make all the above functions available as instance methods on Strings:

class String
  include FunWithStrings
end
