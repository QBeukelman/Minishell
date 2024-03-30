/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 20:36:44 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/03/29 16:18:43 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"

// Definitions of variables
const char* error_messages[] = {
    "ERROR unmatched quote", // ! Don't exit
	"ERROR unmatched pipe",
	"ERROR unmatched redirect",
    "ERROR malloc failure",
	"ERROR cound not open file:"
};

const char* color_codes[] = {
    "\x1B[31m",  // RED
    "\x1B[32m",  // GREEN
    "\x1B[33m",  // YELLOW
    "\x1B[34m"   // BLUE
};

const char* RESET_COLOR = "\x1B[0m";

//!global variables not allowed! should change this