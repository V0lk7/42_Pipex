/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 08:34:48 by jduval            #+#    #+#             */
/*   Updated: 2023/02/20 15:41:46 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"

SUITE(list_suit);
SUITE(path_test);
SUITE(only_cmd);
SUITE(rebuild_cmd);
SUITE(check_all_path);
SUITE(rebuild_str);
SUITE(put_space);
SUITE(find_quote);
SUITE(put_flag);
SUITE(chain_test);

GREATEST_MAIN_DEFS();

int	main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

	/* Tests can also be gathered into test suites. */
	RUN_SUITE(list_suit);
	RUN_SUITE(path_test);
	RUN_SUITE(only_cmd);
	RUN_SUITE(rebuild_cmd);
	RUN_SUITE(check_all_path);
	RUN_SUITE(put_space);
	RUN_SUITE(rebuild_str);
	RUN_SUITE(find_quote);
	RUN_SUITE(put_flag);
	RUN_SUITE(chain_test);

	GREATEST_MAIN_END();        /* display results */
}
