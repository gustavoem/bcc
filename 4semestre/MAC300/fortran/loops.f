      Program loops
      implicit none
      integer :: i
      real :: x
      integer lda, NMAX
      common /constants/ NMAX, lda
      lda = 1
      NMAX = 1000
      print *, NMAX, lda
      do i = 20, 1, -1
        print *, i
      end do
      call subtest
      End program loops     
    
      Subroutine subtest
      integer NMAX, lda
      common /constants/ lda, NMAX
      print *, NMAX, lda
      End subroutine
