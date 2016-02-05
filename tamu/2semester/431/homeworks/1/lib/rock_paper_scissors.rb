class RockPaperScissors

  # Exceptions this class can raise:
  class NoSuchStrategyError < StandardError ; end

  def self.winner(player1, player2)
    winner = player1
    strength = ['R', 'S', 'P'] 
    begin
        z3_player1 = strength.find_index(player1[1])
        z3_player2 = strength.find_index(player2[1])
        # we only change winner if he lost
        if (z3_player1 == (z3_player2 + 1) % 3)
            winner = player2
        end
    rescue
        raise NoSuchStrategyError.new("Strategy must be one of R,P,S")
    end
    winner
  end

  def self.recursive_winner(pair)
    if (pair[0].is_a? String)
      pair
    else
      winner_1 = recursive_winner(pair[0])
      winner_2 = recursive_winner(pair[1])
      winner(winner_1, winner_2)
    end
  end

  def self.tournament_winner(tournament)
    recursive_winner(tournament)
  end

end
