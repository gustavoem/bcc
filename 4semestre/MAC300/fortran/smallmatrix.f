        program bla
            integer, parameter lda = 1000
            double precision, dimension(lda, lda) :: A
            call sub
        end program
        
        subroutine sub
            integer :: NMAX
            print *, NMAX
        end subroutine
