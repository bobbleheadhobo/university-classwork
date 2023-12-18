! Name: Joey Troyer
! Date: 09/26/22
! input: a number to determine the size of the matrix
! output: the time it take to preform gaussian elimination on the matrix
! problem: The task is to create a program that can generate an matrix with random entires
!          and preform gaussian elimination and backsubstitution on the matrix. The goal
!          was to time how long it would take to solve the matrix for each increase in size

PROGRAM gaussian_elimination
    IMPLICIT NONE

    !create all of our variables and arrays
    INTEGER::i,j,x,y,n
    REAL::s, rand, start, finish
    REAL,ALLOCATABLE,DIMENSION(:)::e
    REAL, ALLOCATABLE, DIMENSION(:,:)::a

    read *, n

    ALLOCATE(a(n,n))

    ! Fill the matrix with random values
    do x = 1, n
        do y = 1, n - 1
            call random_number(rand)
            a(x,y) = floor((rand * 1000) + 1)
        end do
    end do


    ! log time at start if algorithm
    CALL cpu_time(start)

    ! perform gaussian elimination
    DO j=1,n
        DO i=j+1,n
            a(i,:)=a(i,:)-a(j,:)*a(i,j)/a(j,j)
        END DO
    END DO


    ALLOCATE(e(n))

    ! perform back traceing
    DO i=n,1,-1
        s=a(i,n+1)
        DO j=i+1,n
            s=s-a(i,j)*e(j)
        END DO
        e(i)=s/a(i,i)
    END DO

    ! log time at end of algorithm
    CALL cpu_time(finish)

    ! print formatted time in seconds
    PRINT'("Time = ",f10.7," seconds.")',(finish - start)

END PROGRAM
