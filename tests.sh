#!/bin/bash
valgrind --leak-check=full ./doom-nukem map_files/map_error_noheader.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_samepoints.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_uncorrect_nb_of_sectors.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_uncorrect_whitespace.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_unlinked_map.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_portal_not_connected.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_less_than_three_points.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_player_out_of_bounds.TEST
valgrind --leak-check=full ./doom-nukem map_files/map_error_lines_cut.TEST
