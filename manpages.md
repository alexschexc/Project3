# Man Pages for reference

You can also look at the output of grep to verify your matches and line numbers.

## strstr
NAME
       strstr, strcasestr - locate a substring

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <string.h>

       char *strstr(const char *haystack, const char *needle);

       #define _GNU_SOURCE         /* See feature_test_macros(7) */
       #include <string.h>

       char *strcasestr(const char *haystack, const char *needle);

DESCRIPTION
       The  strstr() function finds the first occurrence
       of the substring needle in the  string  haystack.
       The  terminating  null  bytes ('\0') are not com‐
       pared.

       The strcasestr() function is like  strstr(),  but
       ignores the case of both arguments.

RETURN VALUE
       These functions return a pointer to the beginning
       of  the  located  substring,  or NULL if the sub‐
       string is not found.

       If needle is the empty string, the  return  value
       is always haystack itself.

ATTRIBUTES
       For an explanation of the terms used in this sec‐
       tion, see attributes(7).
       ┌──────────────┬───────────────┬────────────────┐
       │ Interface    │ Attribute     │ Value          │
       ├──────────────┼───────────────┼────────────────┤
       │ strstr()     │ Thread safety │ MT-Safe        │
       ├──────────────┼───────────────┼────────────────┤
       │ strcasestr() │ Thread safety │ MT-Safe locale │
       └──────────────┴───────────────┴────────────────┘

STANDARDS
       strstr()
              C11, POSIX.1-2008.

       strcasestr()
              GNU.

HISTORY
       strstr()
              POSIX.1-2001, C89.

       strcasestr()
              GNU.

SEE ALSO
       memchr(3),  memmem(3),  strcasecmp(3), strchr(3),
       string(3), strpbrk(3), strsep(3), strspn(3), str‐
       tok(3), wcsstr(3)

## strlen
NAME
       strlen - calculate the length of a string

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <string.h>

       size_t strlen(const char *s);

DESCRIPTION
       The  strlen()  function  calculates the length of
       the string pointed to by s, excluding the  termi‐
       nating null byte ('\0').

RETURN VALUE
       The strlen() function returns the number of bytes
       in the string pointed to by s.

ATTRIBUTES
       For an explanation of the terms used in this sec‐
       tion, see attributes(7).
       ┌─────────────────────┬───────────────┬─────────┐
       │ Interface           │ Attribute     │ Value   │
       ├─────────────────────┼───────────────┼─────────┤
       │ strlen()            │ Thread safety │ MT-Safe │
       └─────────────────────┴───────────────┴─────────┘

STANDARDS
       C11, POSIX.1-2008.

HISTORY
       POSIX.1-2001, C89, SVr4, 4.3BSD.

NOTES
       In cases where the input buffer may not contain a
       terminating  null byte, strnlen(3) should be used
       instead.

SEE ALSO
       string(3), strnlen(3), wcslen(3), wcsnlen(3)

## strcpy
NAME
       stpcpy,  strcpy,  strcat  -  copy  or  catenate a
       string

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <string.h>

       char *stpcpy(char *restrict dst, const char *restrict src);
       char *strcpy(char *restrict dst, const char *restrict src);
       char *strcat(char *restrict dst, const char *restrict src);

   Feature Test Macro Requirements for glibc  (see  fea‐
   ture_test_macros(7)):

       stpcpy():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _GNU_SOURCE

DESCRIPTION
       stpcpy()
       strcpy()
              These functions copy the string pointed to
              by  src,  into  a  string  at  the  buffer
              pointed to by dst.  The programmer is  re‐
              sponsible  for  allocating  a  destination
              buffer large enough, that is,  strlen(src)
              +  1.   For the difference between the two
              functions, see RETURN VALUE.

       strcat()
              This function catenates the string pointed
              to by src, after the string pointed to  by
              dst   (overwriting  its  terminating  null
              byte).  The programmer is responsible  for
              allocating   a  destination  buffer  large
              enough, that is, strlen(dst) + strlen(src)
              + 1.

       An implementation of these functions might be:

           char *
           stpcpy(char *restrict dst, const char *restrict src)
           {
               char  *p;

               p = mempcpy(dst, src, strlen(src));
               *p = '\0';

               return p;
           }

           char *
           strcpy(char *restrict dst, const char *restrict src)
           {
               stpcpy(dst, src);
               return dst;
           }

           char *
           strcat(char *restrict dst, const char *restrict src)
           {
               stpcpy(dst + strlen(dst), src);
               return dst;
           }

RETURN VALUE
       stpcpy()
              This function returns  a  pointer  to  the
              terminating   null   byte  of  the  copied
              string.

       strcpy()
       strcat()
              These functions return dst.

ATTRIBUTES
       For an explanation of the terms used in this sec‐
       tion, see attributes(7).
       ┌─────────────────────┬───────────────┬─────────┐
       │ Interface           │ Attribute     │ Value   │
       ├─────────────────────┼───────────────┼─────────┤
       │ stpcpy(), strcpy(), │ Thread safety │ MT-Safe │
       │ strcat()            │               │         │
       └─────────────────────┴───────────────┴─────────┘

STANDARDS
       stpcpy()
              POSIX.1-2008.

       strcpy()
       strcat()
              C11, POSIX.1-2008.

STANDARDS
       stpcpy()
              POSIX.1-2008.

       strcpy()
       strcat()
              POSIX.1-2001, C89, SVr4, 4.3BSD.

CAVEATS
       The strings src and dst may not overlap.

       If the destination buffer is  not  large  enough,
       the  behavior  is undefined.  See _FORTIFY_SOURCE
       in feature_test_macros(7).

       strcat() can be  very  inefficient.   Read  about
       Shlemiel                the               painter
       ⟨https://www.joelonsoftware.com/2001/12/11/
       back-to-basics/⟩.

EXAMPLES
       #include <err.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>

       int
       main(void)
       {
           char    *p;
           char    *buf1;
           char    *buf2;
           size_t  len, maxsize;

           maxsize = strlen("Hello ") + strlen("world") + strlen("!") + 1;
           buf1 = malloc(sizeof(*buf1) * maxsize);
           if (buf1 == NULL)
               err(EXIT_FAILURE, "malloc()");
           buf2 = malloc(sizeof(*buf2) * maxsize);
           if (buf2 == NULL)
               err(EXIT_FAILURE, "malloc()");

           p = buf1;
           p = stpcpy(p, "Hello ");
           p = stpcpy(p, "world");
           p = stpcpy(p, "!");
           len = p - buf1;

           printf("[len = %zu]: ", len);
           puts(buf1);  // "Hello world!"
           free(buf1);

           strcpy(buf2, "Hello ");
           strcat(buf2, "world");
           strcat(buf2, "!");
           len = strlen(buf2);

           printf("[len = %zu]: ", len);
           puts(buf2);  // "Hello world!"
           free(buf2);

           exit(EXIT_SUCCESS);
       }

SEE ALSO
       strdup(3),  string(3),  wcscpy(3),   string_copy‐
       ing(7)

## strcat
NAME
       stpcpy,  strcpy,  strcat  -  copy  or  catenate a
       string

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <string.h>

       char *stpcpy(char *restrict dst, const char *restrict src);
       char *strcpy(char *restrict dst, const char *restrict src);
       char *strcat(char *restrict dst, const char *restrict src);

   Feature Test Macro Requirements for glibc  (see  fea‐
   ture_test_macros(7)):

       stpcpy():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _GNU_SOURCE

DESCRIPTION
       stpcpy()
       strcpy()
              These functions copy the string pointed to
              by  src,  into  a  string  at  the  buffer
              pointed to by dst.  The programmer is  re‐
              sponsible  for  allocating  a  destination
              buffer large enough, that is,  strlen(src)
              +  1.   For the difference between the two
              functions, see RETURN VALUE.

       strcat()
              This function catenates the string pointed
              to by src, after the string pointed to  by
              dst   (overwriting  its  terminating  null
              byte).  The programmer is responsible  for
              allocating   a  destination  buffer  large
              enough, that is, strlen(dst) + strlen(src)
              + 1.

       An implementation of these functions might be:

           char *
           stpcpy(char *restrict dst, const char *restrict src)
           {
               char  *p;

               p = mempcpy(dst, src, strlen(src));
               *p = '\0';

               return p;
           }

           char *
           strcpy(char *restrict dst, const char *restrict src)
           {
               stpcpy(dst, src);
               return dst;
           }

           char *
           strcat(char *restrict dst, const char *restrict src)
           {
               stpcpy(dst + strlen(dst), src);
               return dst;
           }

RETURN VALUE
       stpcpy()
              This function returns  a  pointer  to  the
              terminating   null   byte  of  the  copied
              string.

       strcpy()
       strcat()
              These functions return dst.

ATTRIBUTES
       For an explanation of the terms used in this sec‐
       tion, see attributes(7).
       ┌─────────────────────┬───────────────┬─────────┐
       │ Interface           │ Attribute     │ Value   │
       ├─────────────────────┼───────────────┼─────────┤
       │ stpcpy(), strcpy(), │ Thread safety │ MT-Safe │
       │ strcat()            │               │         │
       └─────────────────────┴───────────────┴─────────┘

STANDARDS
       stpcpy()
              POSIX.1-2008.

       strcpy()
       strcat()
              C11, POSIX.1-2008.

STANDARDS
       stpcpy()
              POSIX.1-2008.

       strcpy()
       strcat()
              POSIX.1-2001, C89, SVr4, 4.3BSD.

CAVEATS
       The strings src and dst may not overlap.

       If the destination buffer is  not  large  enough,
       the  behavior  is undefined.  See _FORTIFY_SOURCE
       in feature_test_macros(7).

       strcat() can be  very  inefficient.   Read  about
       Shlemiel                the               painter
       ⟨https://www.joelonsoftware.com/2001/12/11/
       back-to-basics/⟩.

EXAMPLES
       #include <err.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>

       int
       main(void)
       {
           char    *p;
           char    *buf1;
           char    *buf2;
           size_t  len, maxsize;

           maxsize = strlen("Hello ") + strlen("world") + strlen("!") + 1;
           buf1 = malloc(sizeof(*buf1) * maxsize);
           if (buf1 == NULL)
               err(EXIT_FAILURE, "malloc()");
           buf2 = malloc(sizeof(*buf2) * maxsize);
           if (buf2 == NULL)
               err(EXIT_FAILURE, "malloc()");

           p = buf1;
           p = stpcpy(p, "Hello ");
           p = stpcpy(p, "world");
           p = stpcpy(p, "!");
           len = p - buf1;

           printf("[len = %zu]: ", len);
           puts(buf1);  // "Hello world!"
           free(buf1);

           strcpy(buf2, "Hello ");
           strcat(buf2, "world");
           strcat(buf2, "!");
           len = strlen(buf2);

           printf("[len = %zu]: ", len);
           puts(buf2);  // "Hello world!"
           free(buf2);

           exit(EXIT_SUCCESS);
       }

SEE ALSO
       strdup(3),  string(3),  wcscpy(3),   string_copy‐
       ing(7)

## opendir
NAME
       opendir, fdopendir - open a directory

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
       DIR *fdopendir(int fd);

   Feature  Test  Macro Requirements for glibc (see fea‐
   ture_test_macros(7)):

       fdopendir():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _GNU_SOURCE

DESCRIPTION
       The opendir() function opens a  directory  stream
       corresponding  to the directory name, and returns
       a pointer to the directory stream.  The stream is
       positioned at the first entry in the directory.

       The fdopendir() function is like  opendir(),  but
       returns  a directory stream for the directory re‐
       ferred to by the open file descriptor fd.   After
       a  successful call to fdopendir(), fd is used in‐
       ternally by the implementation,  and  should  not
       otherwise be used by the application.

RETURN VALUE
       The  opendir() and fdopendir() functions return a
       pointer to the directory stream.  On error,  NULL
       is returned, and errno is set to indicate the er‐
       ror.

ERRORS
       EACCES Permission denied.

       EBADF  fd  is  not a valid file descriptor opened
              for reading.

       EMFILE The per-process limit  on  the  number  of
              open file descriptors has been reached.

       ENFILE The  system-wide limit on the total number
              of open files has been reached.

       ENOENT Directory does not exist, or  name  is  an
              empty string.

       ENOMEM Insufficient memory to complete the opera‐
              tion.

       ENOTDIR
              name is not a directory.

ATTRIBUTES
       For an explanation of the terms used in this sec‐
       tion, see attributes(7).
       ┌─────────────────────┬───────────────┬─────────┐
       │ Interface           │ Attribute     │ Value   │
       ├─────────────────────┼───────────────┼─────────┤
       │ opendir(),          │ Thread safety │ MT-Safe │
       │ fdopendir()         │               │         │
       └─────────────────────┴───────────────┴─────────┘

STANDARDS
       POSIX.1-2008.

STANDARDS
       opendir()
              SVr4, 4.3BSD, POSIX.1-2001.

       fdopendir()
              POSIX.1-2008.  glibc 2.4.

NOTES
       Filename  entries  can  be  read from a directory
       stream using readdir(3).

       The underlying file descriptor of  the  directory
       stream can be obtained using dirfd(3).

       The  opendir()  function  sets  the close-on-exec
       flag for the file descriptor underlying  the  DIR
       *.   The  fdopendir() function leaves the setting
       of the close-on-exec flag unchanged for the  file
       descriptor,  fd.  POSIX.1-200x leaves it unspeci‐
       fied whether a  successful  call  to  fdopendir()
       will  set the close-on-exec flag for the file de‐
       scriptor, fd.

SEE ALSO
       open(2),   closedir(3),   dirfd(3),   readdir(3),
       rewinddir(3), scandir(3), seekdir(3), telldir(3)

## readdir 
NAME
       readdir - read a directory

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include <dirent.h>

       struct dirent *readdir(DIR *dirp);

DESCRIPTION
       The  readdir()  function  returns  a pointer to a
       dirent structure representing the next  directory
       entry in the directory stream pointed to by dirp.
       It returns NULL on reaching the end of the direc‐
       tory stream or if an error occurred.

       In the glibc implementation, the dirent structure
       is defined as follows:

           struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };

       The  only fields in the dirent structure that are
       mandated by POSIX.1 are d_name  and  d_ino.   The
       other  fields are unstandardized, and not present
       on all systems; see VERSIONS.

       The fields of the dirent structure  are  as  fol‐
       lows:

       d_ino  This is the inode number of the file.

       d_off  The value returned in d_off is the same as
              would be returned by calling telldir(3) at
              the  current  position  in  the  directory
              stream.  Be aware that  despite  its  type
              and  name,  the  d_off field is seldom any
              kind  of  directory   offset   on   modern
              filesystems.   Applications  should  treat
              this field as an opaque value,  making  no
              assumptions  about  its contents; see also
              telldir(3).

       d_reclen
              This is the size (in  bytes)  of  the  re‐
              turned  record.   This  may  not match the
              size of  the  structure  definition  shown
              above; see VERSIONS.

       d_type This field contains a value indicating the
              file type, making it possible to avoid the
              expense of calling lstat(2) if further ac‐
              tions depend on the type of the file.

              When  a suitable feature test macro is de‐
              fined (_DEFAULT_SOURCE since  glibc  2.19,
              or _BSD_SOURCE on glibc 2.19 and earlier),
              glibc  defines  the  following  macro con‐
              stants for the value returned in d_type:

              DT_BLK      This is a block device.

              DT_CHR      This is a character device.

              DT_DIR      This is a directory.

              DT_FIFO     This is a named pipe (FIFO).

              DT_LNK      This is a symbolic link.

              DT_REG      This is a regular file.

              DT_SOCK     This is a UNIX domain socket.

              DT_UNKNOWN  The file type could not be de‐
                          termined.

              Currently, only  some  filesystems  (among
              them:  Btrfs,  ext2,  ext3, and ext4) have
              full support for returning the  file  type
              in d_type.  All applications must properly
              handle a return of DT_UNKNOWN.

       d_name This  field  contains  the null terminated
              filename; see VERSIONS.

       The data returned by readdir() may be overwritten
       by subsequent calls to readdir() for the same di‐
       rectory stream.

RETURN VALUE
       On success, readdir()  returns  a  pointer  to  a
       dirent  structure.  (This structure may be stati‐
       cally allocated; do not attempt to free(3) it.)

       If the end of the directory  stream  is  reached,
       NULL is returned and errno is not changed.  If an
       error  occurs,  NULL is returned and errno is set
       to indicate the error.   To  distinguish  end  of
       stream  from  an  error, set errno to zero before
       calling readdir() and then check the value of er‐
       rno if NULL is returned.

ERRORS
       EBADF  Invalid directory stream descriptor dirp.

ATTRIBUTES
       For an explanation of the terms used in this sec‐
       tion, see attributes(7).
       ┌───────────┬───────────────┬──────────────────────────┐
       │ Interface │ Attribute     │ Value                    │
       ├───────────┼───────────────┼──────────────────────────┤
       │ readdir() │ Thread safety │ MT-Unsafe race:dirstream │
       └───────────┴───────────────┴──────────────────────────┘

       In    the    current    POSIX.1     specification
       (POSIX.1-2008),  readdir()  is not required to be
       thread-safe.  However, in modern  implementations
       (including  the glibc implementation), concurrent
       calls to readdir() that specify different  direc‐
       tory  streams  are  thread-safe.   In cases where
       multiple threads must read from the  same  direc‐
       tory  stream,  using readdir() with external syn‐
       chronization is still preferable to  the  use  of
       the  deprecated readdir_r(3) function.  It is ex‐
       pected that a future version of POSIX.1 will  re‐
       quire  that readdir() be thread-safe when concur‐
       rently employed on different directory streams.

VERSIONS
       Only the fields d_name and (as an XSI  extension)
       d_ino  are  specified  in  POSIX.1.   Other  than
       Linux, the d_type field is available mainly  only
       on  BSD systems.  The remaining fields are avail‐
       able on many, but not all systems.  Under  glibc,
       programs  can  check  for the availability of the
       fields not defined in POSIX.1 by testing  whether
       the         macros         _DIRENT_HAVE_D_NAMLEN,
       _DIRENT_HAVE_D_RECLEN,   _DIRENT_HAVE_D_OFF,   or
       _DIRENT_HAVE_D_TYPE are defined.

   The d_name field
       The  dirent  structure  definition shown above is
       taken from  the  glibc  headers,  and  shows  the
       d_name field with a fixed size.

       Warning: applications should avoid any dependence
       on  the  size of the d_name field.  POSIX defines
       it as char d_name[], a character array of unspec‐
       ified size, with at most NAME_MAX characters pre‐
       ceding the terminating null byte ('\0').

       POSIX.1 explicitly notes that this  field  should
       not  be  used  as  an  lvalue.  The standard also
       notes that the use of  sizeof(d_name)  is  incor‐
       rect;  use strlen(d_name) instead.  (On some sys‐
       tems, this field is defined as  char  d_name[1]!)
       By  implication, the use sizeof(struct dirent) to
       capture the size of the record including the size
       of d_name is also incorrect.

       Note that while the call

           fpathconf(fd, _PC_NAME_MAX)

       returns the value 255 for  most  filesystems,  on
       some   filesystems   (e.g.,   CIFS,  Windows  SMB
       servers), the null-terminated  filename  that  is
       (correctly)  returned  in d_name can actually ex‐
       ceed this size.   In  such  cases,  the  d_reclen
       field  will contain a value that exceeds the size
       of the glibc dirent structure shown above.

STANDARDS
       POSIX.1-2008.

HISTORY
       POSIX.1-2001, SVr4, 4.3BSD.

NOTES
       A directory stream is opened using opendir(3).

       The order in which filenames are read by  succes‐
       sive calls to readdir() depends on the filesystem
       implementation;  it  is  unlikely  that the names
       will be sorted in any fashion.

SEE ALSO
       getdents(2),  read(2),   closedir(3),   dirfd(3),
       ftw(3),  offsetof(3),  opendir(3),  readdir_r(3),
       rewinddir(3), scandir(3), seekdir(3), telldir(3)

## lstat
PROLOG
       This  manual  page  is part of the POSIX Program‐
       mer's Manual.  The Linux implementation  of  this
       interface  may  differ (consult the corresponding
       Linux manual page for details of Linux behavior),
       or the interface may not be implemented on Linux.

NAME
       lstat — get file status

SYNOPSIS
       #include <sys/stat.h>

       int lstat(const char *restrict path, struct stat *restrict buf);

DESCRIPTION
       Refer to fstatat().

COPYRIGHT
       Portions of this text are  reprinted  and  repro‐
       duced   in   electronic   form   from   IEEE  Std
       1003.1-2017, Standard for Information  Technology
       --  Portable  Operating System Interface (POSIX),
       The Open Group Base Specifications Issue 7,  2018
       Edition,  Copyright  (C) 2018 by the Institute of
       Electrical and Electronics Engineers, Inc and The
       Open Group.  In the event of any discrepancy  be‐
       tween  this version and the original IEEE and The
       Open Group Standard, the original  IEEE  and  The
       Open  Group Standard is the referee document. The
       original  Standard  can  be  obtained  online  at
       http://www.opengroup.org/unix/online.html .

       Any  typographical  or formatting errors that ap‐
       pear in this page are most likely  to  have  been
       introduced  during  the  conversion of the source
       files to man page format. To report such  errors,
       see  https://www.kernel.org/doc/man-pages/report‐
       ing_bugs.html .

IEEE/The Open Group       2017                 LSTAT(3P)

## stat
NAME
       stat - display file or file system status

SYNOPSIS
       stat [OPTION]... FILE...

DESCRIPTION
       Display file or file system status.

       Mandatory arguments to long options are mandatory
       for short options too.

       -L, --dereference
              follow links

       -f, --file-system
              display file system status instead of file
              status

       --cached=MODE
              specify how to use cached attributes; use‐
              ful on remote file systems. See MODE below

       -c  --format=FORMAT
              use  the  specified  FORMAT instead of the
              default; output a newline after  each  use
              of FORMAT

       --printf=FORMAT
              like --format, but interpret backslash es‐
              capes,  and  do  not  output  a  mandatory
              trailing newline; if you want  a  newline,
              include \n in FORMAT

       -t, --terse
              print the information in terse form

       --help display this help and exit

       --version
              output version information and exit

       The  MODE  argument  of  --cached can be: always,
       never, or default.  'always' will use cached  at‐
       tributes  if available, while 'never' will try to
       synchronize with the latest attributes, and  'de‐
       fault'  will  leave  it up to the underlying file
       system.

       The valid format  sequences  for  files  (without
       --file-system):

       %a     permission  bits in octal (see '#' and '0'
              printf flags)

       %A     permission bits and  file  type  in  human
              readable form

       %b     number of blocks allocated (see %B)

       %B     the  size  in bytes of each block reported
              by %b

       %C     SELinux security context string

       %d     device number in decimal (st_dev)

       %D     device number in hex (st_dev)

       %Hd    major device number in decimal

       %Ld    minor device number in decimal

       %f     raw mode in hex

       %F     file type

       %g     group ID of owner

       %G     group name of owner

       %h     number of hard links

       %i     inode number

       %m     mount point

       %n     file name

       %N     quoted file name with dereference if  sym‐
              bolic link

       %o     optimal I/O transfer size hint

       %s     total size, in bytes

       %r     device type in decimal (st_rdev)

       %R     device type in hex (st_rdev)

       %Hr    major  device type in decimal, for charac‐
              ter/block device special files

       %Lr    minor device type in decimal, for  charac‐
              ter/block device special files

       %t     major  device  type  in  hex,  for charac‐
              ter/block device special files

       %T     minor device  type  in  hex,  for  charac‐
              ter/block device special files

       %u     user ID of owner

       %U     user name of owner

       %w     time  of  file birth, human-readable; - if
              unknown

       %W     time of file birth, seconds since Epoch; 0
              if unknown

       %x     time of last access, human-readable

       %X     time of last access, seconds since Epoch

       %y     time  of  last  data   modification,   hu‐
              man-readable

       %Y     time  of  last  data modification, seconds
              since Epoch

       %z     time of last status change, human-readable

       %Z     time of last status change, seconds  since
              Epoch

       Valid format sequences for file systems:

       %a     free blocks available to non-superuser

       %b     total data blocks in file system

       %c     total file nodes in file system

       %d     free file nodes in file system

       %f     free blocks in file system

       %i     file system ID in hex

       %l     maximum length of filenames

       %n     file name

       %s     block size (for faster transfers)

       %S     fundamental block size (for block counts)

       %t     file system type in hex

       %T     file system type in human readable form

   --terse is equivalent to the following FORMAT:
              %n  %s %b %f %u %g %D %i %h %t %T %X %Y %Z
              %W %o

   --terse --file-system is equivalent to the  following
       FORMAT:
              %n %i %l %t %s %S %b %f %a %c %d

       Your  shell  may  have  its  own version of stat,
       which usually supersedes  the  version  described
       here.  Please refer to your shell's documentation
       for details about the options it supports.

AUTHOR
       Written by Michael Meskes.

REPORTING BUGS
       GNU         coreutils         online        help:
       <https://www.gnu.org/software/coreutils/>
       Report any translation bugs to  <https://transla‐
       tionproject.org/team/>

COPYRIGHT
       Copyright  ©  2024 Free Software Foundation, Inc.
       License  GPLv3+:  GNU  GPL  version  3  or  later
       <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and
       redistribute  it.   There  is NO WARRANTY, to the
       extent permitted by law.

SEE ALSO
       stat(2), statfs(2), statx(2)

       Full   documentation   <https://www.gnu.org/soft‐
       ware/coreutils/stat>
       or  available locally via: info '(coreutils) stat
       invocation'

GNU coreutils 9.5      March 2024                STAT(1)

