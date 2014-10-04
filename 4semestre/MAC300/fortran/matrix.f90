Program matrix
    double precision, dimension(1000, 1000) :: A
    double precision, dimension(1000) :: b
    integer :: n
    call readMatrix(A, b, n)   
    call printMatrix(A, n) 
    call printVector(b, n)
End Program matrix

Subroutine swap(x, y)
    double precision temp
    double precision, intent(out) :: x, y
    temp = x
    x = y
    y = temp
End Subroutine swap

Subroutine readMatrix(A, b, n)
    double precision, dimension(1000, 1000), intent(out) :: A
    double precision, dimension(1000), intent(out) :: b
    integer, intent(out) :: n
    integer :: i, j
    integer :: nsquare
    read *, n
    nsquare = n ** 2
    do k = 1, nsquare
        read *, i, j, A(i, j)
    end do
    do k = 1, n
        read *, i, b(i)
    end do
End Subroutine

Subroutine printMatrix(A, n)
    implicit none
    
    integer, intent(in) :: n
    double precision, intent(in) :: A(n, n)

    integer :: i, j

    do i = 1, n
        do j = 1, n
            print "(f7.3$)", A(i, j)
        end do
        print *,""
    end do
End Subroutine

Subroutine printVector(v, n)
    implicit none

    integer, intent(in) :: n
    double precision, intent(in) :: v(n)

    integer :: i

    do i = 1, n
        print "(f7.3)", v(i)
    end do
End Subroutine
