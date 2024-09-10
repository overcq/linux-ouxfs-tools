/*******************************************************************************
*   ___   [obszar]
*  ¦OUX¦  [system programowania]
*  ¦/C+¦  [rodzaj składnika]
*   ---   [nazwa składnika]
*         [tytuł elementu]
* ©overcq                on ‟Gentoo Linux 23.0” “x86_64”              2024‒8‒7 f
*******************************************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
//==============================================================================
#define H_oux_J_align_up_p(p,t)     (( void * )(( uint64_t )(p) + sizeof(t) - 1 - (( uint64_t )(p) + sizeof(t) - 1 ) % sizeof(t) ))
//==============================================================================
int
main( int argc
, char *argv[]
){  if( argc != 3 )
        return 1;
    char *end;
    if( *argv[2] == '\0' )
        return 1;
    long sector_size = strtol( argv[2], &end, 0 );
    if( *end != '\0'
    || ( sector_size != 512
      && sector_size != 4096
    ))
        return 1;
    int fd = open( argv[1], O_WRONLY );
    if( !~fd )
    {   perror( argv[0] );
        return 1;
    }
    char *sector = calloc( 1, sector_size );
    if( !sector )
    {   perror( argv[0] );
        close(fd);
        return 1;
    }
    char *data = sector;
    strcpy( data, "OUXFS" );
    data += 6;
    *data = __builtin_ctz( sector_size );
    data++;
    data = H_oux_J_align_up_p( data, uint64_t );
    uint64_t value = 0;
    memcpy(( void * )data, ( void * )&value, sizeof(value) ); // block_table_n
    data += sizeof(value);
    memcpy(( void * )data, ( void * )&value, sizeof(value) ); // block_table_block_table_n
    data += sizeof(value);
    memcpy(( void * )data, ( void * )&value, sizeof(value) ); // block_table_directory_table_start
    data += sizeof(value);
    memcpy(( void * )data, ( void * )&value, sizeof(value) ); // block_table_directory_table_n
    data += sizeof(value);
    memcpy(( void * )data, ( void * )&value, sizeof(value) ); // block_table_file_table_start
    data += sizeof(value);
    memcpy(( void * )data, ( void * )&value, sizeof(value) ); // block_table_file_table_n
    if( write( fd, sector, sector_size ) != sector_size )
    {   perror( argv[0] );
        close(fd);
        return 1;
    }
    close(fd);
    free(sector);
    return 0;
}
/******************************************************************************/
