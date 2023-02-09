/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 08:34:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/09 17:34:30 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"

SUITE(list_suit);
SUITE(file_test);
SUITE(path_test);

GREATEST_MAIN_DEFS();

int	main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

	/* Tests can also be gathered into test suites. */
	RUN_SUITE(list_suit);
	RUN_SUITE(file_test);
	RUN_SUITE(path_test);

	GREATEST_MAIN_END();        /* display results */
}
