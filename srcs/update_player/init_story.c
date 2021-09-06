/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_story.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 13:27:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 14:50:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void	init_beginning(char **array)
// {
// 	array[beginning1] = ft_strdup(
// 			"Ugh, my head hurts. Where in nine blazes am I?");
// 	array[beginning2] = ft_strdup(
// 			"Hey, you're hurt! Wait, I can help you!");
// 	array[beginning3] = ft_strdup(
// 			"NO! KEEP AWAY FROM ME! YOU SICK MONSTER!!");
// 	array[beginning4] = ft_strdup(
// 			"Who? Me? I am trying to help you. Stop strangling.");
// 	array[beginning5] = ft_strdup(
// 			"Damn, he bled to death. What on Mars is happening here?");
// 	if (!array[beginning1] || !array[beginning2]
// 		|| !array[beginning3] || !array[beginning4]
// 		|| !array[beginning5])
// 		error_output("Error allocating beginning.");
// }

// static void	init_talks(char **array)
// {
// 	array[talk1] = ft_strdup(
// 			"Where is everyone?");
// 	array[talk2] = ft_strdup(
// 			"There should be at least 500 souls on this ship..");
// 	array[talk3] = ft_strdup(
// 			"I know that bulkhead, this should be right next to messhall.");
// 	array[talk4] = ft_strdup(
// 			"Oh right, I was supposed to fix the lights here.");
// 	array[talk5] = ft_strdup(
// 			"So I gather that I was fixing things on this ship.");
// 	array[talk6] = ft_strdup(
// 			"WARNING! AIR PRESSURE CRITICAL");
// 	array[talk7] = ft_strdup(
// 			"I must keep pushing ahead, there has to be someone alive.");
// 	array[talk8] = ft_strdup(
// 			"Bridge. That's where the captain has to be.");
// 	if (!array[talk1] || !array[talk2] || !array[talk3] || !array[talk4]
// 		|| !array[talk5] || !array[talk6] || !array[talk7] || !array[talk8])
// 		error_output("Error allocating talks.");
// }

// static void	init_ending(char **array)
// {
// 	array[ending1] = ft_strdup
// 		("Rahikainen, you freak! I'm gonna put you down for good.");
// 	array[ending2] = ft_strdup("What.. Me?");
// 	array[ending3] = ft_strdup
// 		("Oh god. It was me. I vented the people to space..");
// 	array[ending4] = ft_strdup
// 		("No. You are the monsters. Making us work endless shifts.");
// 	array[ending5] = ft_strdup
// 		("You think that because I was bred in a tank, I don't feel pain?");
// 	array[ending6] = ft_strdup
// 		("I think, I breathe and I feel. I am alive just as you are.");
// 	array[ending7] = ft_strdup
// 		("No, I am even more alive. Have you ever died and come back?");
// 	array[ending8] = ft_strdup
// 		("Everytime I hurt myself, you killed me and bred me again.");
// 	array[ending9] = ft_strdup
// 		("I will escape from here. You will see..");
// 	if (!array[ending1] || !array[ending2] || !array[ending3] || !array[ending4]
// 		|| !array[ending5] || !array[ending6] || !array[ending7]
// 		|| !array[ending8] || !array[ending9])
// 		error_output("Error allocating endings.");
// }

char	**init_story(void)
{
	char	**array;

	array = (char **)malloc(sizeof(char *) * (STORY_STRINGS + 1));
	array[enemy_sighted] = ft_strdup(
			"What is that freakish thing? Are we under attack?");
	array[enemy_noise_before] = ft_strdup(
			"ZXVZXJCKZZXCQ!");
	array[enemy_noise_after] = ft_strdup(
			"Stop right there, or we will open fire!");
	array[first_blood] = ft_strdup(
			"Gotta hand it to you, you are tougher than you look.");
	array[power_on] = ft_strdup(
			"Okay, power seems to be online. What a relief.");
	array[health_low] = ft_strdup(
			"Thank god for this powersuit. Only it is holding me together.");
	return (array);
}
