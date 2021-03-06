/*
   Copyright (c) 2007 Sergio Castillo P�rez

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ------------------------------------------------------------------------- */

#ifndef _TFTP_H_
	#define _TFTP_H_
	#define VERSION			"0.1.0"

	#define RFC1350_OP_RRQ		1	/* Read request   */
	#define RFC1350_OP_WRQ		2	/* Write request  */
	#define RFC1350_OP_DATA		3	/* Data           */
	#define RFC1350_OP_ACK		4	/* Acknowledgment */
	#define RFC1350_OP_ERROR	5	/* Error          */

	#define RFC1350_ERR_NOTDEF		0	/* Not defined, see err. messsage   */
	#define RFC1350_ERR_FNOTFOUND	1	/* File not found                   */
	#define RFC1350_ERR_ACCESS		2	/* Access violation                 */
	#define RFC1350_ERR_DISKFULL	3	/* Disk full or allocation exceeded */
	#define RFC1350_ERR_ILEGALOP	4	/* Illegal TFTP operation           */
	#define RFC1350_ERR_UKNOWID		5	/* Unknown transfer ID              */
	#define RFC1350_ERR_FEXISTS		6	/* File already exists              */
	#define RFC1350_ERR_NOUSER		7	/* No such user                     */

	#define RFC1350_PORT		69	/* Transport TFTP port  */
	#define RFC1350_BLOCKSIZE	512	/* Max. data block size */

	#define u_int16_t unsigned short
	#define OPCODE(addr) (ntohs(* ((u_int16_t *) addr)))

	/* ------------------------------------------------------------------------- */

	typedef enum {
		FALSE,
		TRUE
	} BOOL;

	/* ------------------------------------------------------------------------- */

	/*
	   Read/Write header. See also RFC1350.

		 .-------+------------+------+------------+------.
	   RRQ/  | 01/02 |  Filename  |   0  |    Mode    |   0  |
	   WRQ   '-------+------------+------+------------+------'
		  2 bytes    string   1 byte     string    1 byte

	*/

	#define MAXPATH_STRLEN 		1024	/* Should be enough for all systems */
	#define MAXMODE_STRLEN 		8		/* octet, mail, netascii */

	typedef struct {
		u_int16_t opcode;
		char filename[MAXPATH_STRLEN + 1];
		char mode[MAXMODE_STRLEN + 1];
		char tout[8];
		char toutv[4];
	} tftp_rwq_hdr;


	/* ------------------------------------------------------------------------- */

	/*
	   Data header. See also RFC1350.

		 .-------+------------+----------------.
	   DATA  | 03    |   Block #  |      Data      |
		 '-------+------------+----------------'
		  2 bytes    2 bytes     1..512 bytes
	*/

	typedef struct {
		u_int16_t opcode;
		u_int16_t num_block;
		char data[RFC1350_BLOCKSIZE];
	} tftp_data_hdr;

	/* ------------------------------------------------------------------------- */

	/*
	   Acknowlege header. See also RFC1350.

		 .-------+------------.
	   ACK   | 04    |   Block #  |
		 '-------+------------'
		  2 bytes  2 bytes
	*/

	typedef struct {
		u_int16_t opcode;
		u_int16_t num_block;
	} tftp_ack_hdr;

	/* ------------------------------------------------------------------------- */

	/*
	   Error header. See also RFC1350.

		 .-------+------------+------------+------.
	   ERROR | 05    |  ErrorCode |   ErrMsg   |   0  |
		 '-------+------------+------------+------'
		  2 bytes  2 bytes        string    1 byte
	*/

	#define MAX_ERROR_STRLEN 300

	typedef struct {
		u_int16_t opcode;
		u_int16_t code;
		char message[MAX_ERROR_STRLEN + 1];
	} tftp_error_hdr;
#endif

/* ------------------------------------------------------------------------- */
