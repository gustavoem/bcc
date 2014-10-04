subroutine xsquare(y)
    integer, intent(inout) :: y
    y = y ** 2
    print *, 'xdentro: ',y
end subroutine xsquare

function func(i) result(z)
    integer, intent(in) :: i
    integer             :: j
    j = i ** 3
end function func

Program bla
    implicit none
    integer :: x
    integer :: func
    integer y, res

    x = 2
    call xsquare(x)
    print *,'xfora: ',x, ' funcao: ', func(x)
End program bla

