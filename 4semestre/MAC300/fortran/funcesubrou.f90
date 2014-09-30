subroutine xsquare(y)
    integer, intent(inout) :: y
    y = y ** 2
    print *, 'xdentro: ',y
end subroutine xsquare

Program bla
    implicit none
    integer :: x
    x = 6
    call xsquare(x)
    print *,'xfora: ',x
End program bla

