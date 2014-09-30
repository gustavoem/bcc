Program eps
    real :: ant, next 
    ant = 1
    next = ant / 2
    do while (next /= ant)
        ant = next
        next = next / 2
        print *, next
    end do
End program eps 

