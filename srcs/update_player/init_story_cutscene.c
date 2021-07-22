/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_story_cutscene.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:40:34 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/13 11:34:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../headers/doom_nukem.h"

// static void	add_first_cutscene_part(char **array)
// {
// 	array[cutscene1] = ft_strdup(
// 			"[LOG 2213-02-21]: To anyone who will find this, I escaped");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nbarely from the station 11-EASIF, which I had called home.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nI have been drifting in the escape pod for some time now.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nMy supplies are low, and I will most likely perish in few days.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nMost of my memories have returned. They are not pleasant ones.");
// }

// static void	add_second_cutscene_part(char **array)
// {
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nI was a tank-bred marine. If you don't know what that is, ask");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nyour parents. Their generation came up with this great idea");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nto breed us to help mankind to explore the stars. They");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nrealized our memories could be stored, spliced");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nand given to others. We became warriors, scholars and");
// }

// static void	add_third_cutscene_part(char **array)
// {
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nand given to others. We became warriors, scholars and");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nmechanics in the fringes of the galaxy, who didn't have to");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nfear death. From shoulder of Orion to Plutition camps of Titan,");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nI had fought against beings that would haunt your dreams.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nI was ripped to shreds, blasted to pieces and burnt alive");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\n more times than I care to remember. After that, my mind");
// }

// static void	add_fourth_cutscene_part(char **array)
// {
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nwas repurposed as a mechanic and moved to Pegasus sector.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nThat was beginning of my abusement. I was like trash.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nto be used and discarded and used again. But not this");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\ntime. I am out of range of any long range transfers");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nso my death will be finally permanent.");
// 	if (!array[cutscene1])
// 		error_output("Error when allocating story cutscene");
// 	array[cutscene1] = ft_strjoin(array[cutscene1],
// 			"\nGood bye. No more of these dreams.");
// }

// void	init_cutscene(char **array)
// {
// 	add_first_cutscene_part(array);
// 	add_second_cutscene_part(array);
// 	add_third_cutscene_part(array);
// 	add_fourth_cutscene_part(array);
// 	array[cutscene2] = ft_strdup(
// 			"[LOG 2213-02-22]: SHIP IN RANGE.\nTRANSFER DATA.\nTRANSFER COMPLETE.");
// }
