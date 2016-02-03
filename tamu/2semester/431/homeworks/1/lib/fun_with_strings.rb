module FunWithStrings
  def palindrome?
    s = self.downcase.gsub(/\W+/, "")
    s == s.reverse
  end

  def count_words
    v = self.downcase.split(/\W+/).reject{|s| s.empty?}
    hash = Hash.new(0)
    v.each{|x| hash[x] += 1}
    hash
  end

  def anagram_groups
    word_v = self.split(/\s+/).reject{|s| s.empty?}
    groups = []
    groups = word_v.group_by{|word| word.downcase.chars.sort}.values
    groups
  end

end

# make all the above functions available as instance methods on Strings:

class String
  include FunWithStrings
end
