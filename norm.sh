# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norm.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/22 16:26:40 by dstumpf           #+#    #+#              #
#    Updated: 2026/09/22 16:39:09 by dstumpf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/bash

#find all the .c and .h files except for the dummy_map_generator.c which shouldnt be checked since it is not part of the actual project
#run norminette on all of then and store in output variable
output=$(find . \( -name "*.c" -o -name "*.h" \) ! -name "dummy_map_generator.c" -exec norminette {} +)

#find all the lines containing errors of said output
errors=$(printf "%s\n" "$output" | grep -v "Setting locale to" | grep -v "OK!")

#check if error variable is empty, in which case exit OK
if [ -z "$errors" ]; then
    exit 0
fi

#otherwise there are errors
printf "%s\n" "$errors"
exit 1
