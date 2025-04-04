/*******************************************************************************
*   ___   public
*  ¦OUX¦  C
*  ¦/C+¦  commandline utility
*   ---   OUX filesystem
*         test
* ©overcq                on ‟Gentoo Linux 23.0” “x86_64”              2024‒7‒7 H
*******************************************************************************/
#include <sys/file.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//==============================================================================
int
main(
  int argc
, char *argv[]
){  if( argc != 2 )
        return EINVAL;
    const char *name = argv[1];
    long device_i = syscall( 700, "/dev/sdb" );
    printf( "device_i: %ld\n", device_i );
    if( !~device_i )
    {   perror( "ouxfs" );
        return 1;
    }
    puts( "0" );
    int error = 0;
    uint64_t directory;
    if( !~syscall( 703, device_i, ~0UL, name, &directory ))
    {   perror( "ouxfs" );
        error = 1;
        goto Error_0;
    }
    puts( "1" );
    uint64_t file;
    if( !~syscall( 705, device_i, directory, name, &file ))
    {   perror( "ouxfs" );
        error = 1;
        goto Error_0;
    }
    puts( "2" );
    uint64_t n_1 = 0, *list_0;
    if( !~syscall( 707, device_i, ~0UL, &n_1, list_0 ))
    {   perror( "ouxfs" );
        error = 1;
        goto Error_0;
    }
    puts( "3" );
    list_0 = calloc( n_1, sizeof( *list_0 ));
    if( !list_0 )
    {   perror( "ouxfs" );
        error = 1;
        goto Error_0;
    }
    puts( "4" );
    uint64_t n_2 = n_1;
    if( !~syscall( 707, device_i, ~0UL, &n_2, list_0 ))
    {   perror( "ouxfs" );
        error = 1;
        free( list_0 );
        goto Error_0;
    }
    if( n_2 != n_1 )
    {   error = 1;
        free( list_0 );
        goto Error_0;
    }
    puts( "5" );
    for( uint64_t i = 0; i != n_1; i++ )
    {   printf( "nsfod: %lu/%lu\n", i, n_1 );
        uint64_t n_1 = 0;
        char *name;
        if( !~syscall( 709, device_i, list_0[i], &n_1, name ))
        {   perror( "ouxfs" );
            error = 1;
            free( list_0 );
            goto Error_0;
        }
        name = malloc( n_1 );
        if( !name )
        {   perror( "ouxfs" );
            error = 1;
            free( list_0 );
            goto Error_0;
        }
        uint64_t n_2 = n_1;
        if( !~syscall( 709, device_i, list_0[i], &n_2, name ))
        {   perror( "ouxfs" );
            error = 1;
            free( list_0 );
            goto Error_0;
        }
        if( n_2 != n_1 )
        {   error = 1;
            free(name);
            free( list_0 );
            goto Error_0;
        }
        printf( "%lu. %lu, \"%s\"\n", i, list_0[i], name );
        /*char *p = realloc( name, n_1 + 1 );
        if( !p )
        {   error = 1;
            free(name);
            free( list_0 );
            goto Error_0;
        }
        name = p;
        name[ n_1 - 1 ] = '_';
        name[ n_1 ] = '\0';
        if( !~syscall( 710, device_i, list_0[i], name ))
        {   perror( "ouxfs" );
            error = 1;
            free(name);
            free( list_0 );
            goto Error_0;
        }
        free(name);
        puts( "6" );*/
        n_1 = 0;
        uint64_t *list_1;
        if( !~syscall( 708, device_i, list_0[i], &n_1, list_1 ))
        {   perror( "ouxfs" );
            error = 1;
            free( list_0 );
            goto Error_0;
        }
        list_1 = calloc( n_1, sizeof( *list_1 ));
        if( !list_0 )
        {   perror( "ouxfs" );
            error = 1;
            free( list_0 );
            goto Error_0;
        }
        n_2 = n_1;
        if( !~syscall( 708, device_i, list_0[i], &n_1, list_1 ))
        {   perror( "ouxfs" );
            error = 1;
            free( list_1 );
            free( list_0 );
            goto Error_0;
        }
        if( n_2 != n_1 )
        {   error = 1;
            free( list_1 );
            free( list_0 );
            goto Error_0;
        }
        puts( "7" );
        for( uint64_t i = 0; i != n_1; i++ )
        {   uint64_t n_1 = 0;
            char *name;
            if( !~syscall( 711, device_i, list_1[i], &n_1, name ))
            {   perror( "ouxfs" );
                error = 1;
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            name = malloc( n_1 );
            if( !name )
            {   perror( "ouxfs" );
                error = 1;
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            uint64_t n_2 = n_1;
            if( !~syscall( 711, device_i, list_1[i], &n_1, name ))
            {   perror( "ouxfs" );
                error = 1;
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            if( n_2 != n_1 )
            {   error = 1;
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            printf( "\t%lu. %lu, \"%s\"\n", i, list_1[i], name );
            char *p = realloc( name, n_1 + 1 );
            if( !p )
            {   error = 1;
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            name = p;
            name[ n_1 - 1 ] = '_';
            name[ n_1 ] = '\0';
            if( !~syscall( 712, device_i, list_1[i], name ))
            {   perror( "ouxfs" );
                error = 1;
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            puts( "8" );
            if( !~syscall( 715, device_i, list_1[i], ~0UL ))
            {   perror( "ouxfs" );
                error = 1;
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            puts( "9" );
            if( !~syscall( 717, device_i, list_1[i], LOCK_EX ))
            {   perror( "ouxfs" );
                error = 1;
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            puts( "10" );
            if( !~syscall( 719, device_i, list_1[i], 0, &n_1, name ))
            {   perror( "ouxfs" );
                error = 1;
                syscall( 716, device_i, list_1[i], LOCK_UN );
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            if( n_2 != n_1 )
            {   error = 1;
                syscall( 717, device_i, list_1[i], LOCK_UN );
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            puts( "11" );
            n_2 = --n_1;
            if( !~syscall( 716, device_i, list_1[i], n_1 ))
            {   perror( "ouxfs" );
                error = 1;
                syscall( 716, device_i, list_1[i], LOCK_UN );
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            puts( "12" );
            memset( name, 0, n_1 + 1 );
            if( !~syscall( 718, device_i, list_1[i], 0, &n_1, name ))
            {   perror( "ouxfs" );
                error = 1;
                syscall( 716, device_i, list_1[i], LOCK_UN );
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            if( n_2 != n_1 )
            {   error = 1;
                syscall( 717, device_i, list_1[i], LOCK_UN );
                free(name);
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
            printf( "\tread \"%s\"\n", name );
            free(name);
            if( !~syscall( 717, device_i, list_1[i], LOCK_UN ))
            {   perror( "ouxfs" );
                error = 1;
                free( list_1 );
                free( list_0 );
                goto Error_0;
            }
        }
        free( list_1 );
    }
    free( list_0 );
    if( !~syscall( 702, device_i ))
    {   perror( "ouxfs" );
        error = 1;
    }
Error_0:
    puts( "13" );
    if( !~syscall( 701, device_i ))
    {   perror( "ouxfs" );
        error = 1;
    }
    return error;
}
