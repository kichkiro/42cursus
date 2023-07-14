/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:32:20 by kichkiro          #+#    #+#             */
/*   Updated: 2023/07/14 12:10:54 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// Libraries ------------------------------------------------------------------>

#include "Weapon.hpp"

// Class ---------------------------------------------------------------------->

class HumanB
{
	public:
		HumanB(string name, string weapon);
		~HumanB(void);

		string	name;
		Weapon	weapon;

		void	attack(void);
};
