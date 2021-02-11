/**
 * @copyright
 * @file stl_helper.cpp
 * @author Andrea Gianarda
 * @date 06th of October 2020
 * @brief STL Helper
 */

#include "app/utility/cpp/stl_helper.h"

const std::string app::utility::findAndReplaceString(std::string text, const std::string & searchString, const std::string & replacingString) {

	if (searchString.empty() == false) {
		std::size_t position = 0;
		while ((position != std::string::npos) && (position < text.size())) {
			position = text.find(searchString, position);
			if (position != std::string::npos) {
				if (replacingString.empty() == true) {
					text.erase(position, searchString.size());
				} else {
					text.replace(position, searchString.size(), replacingString);
				}
				position++;
			}
		}
	}

	return text;
}

const std::string app::utility::removeTrailingCharacter(std::string text, const std::string & trailingCharacters) {
	std::size_t lastValidCharacter = text.find_last_not_of(trailingCharacters);
	if (lastValidCharacter != std::string::npos) {
		text.erase(lastValidCharacter + 1);
	} else {
		text.clear();
	}

	return text;
}

const std::string app::utility::removeLeadingCharacter(std::string text, const std::string & leadingCharacters) {
	std::size_t firstValidCharacter = text.find_first_not_of(leadingCharacters);
	if (firstValidCharacter != std::string::npos) {
		text.erase(0, firstValidCharacter);
	} else {
		text.clear();
	}

	return text;
}

const std::string app::utility::removeLeadingAndTrailingCharacter(std::string text, const std::string & leadingCharacters, const std::string & trailingCharacters) {
	text = app::utility::removeTrailingCharacter(text, trailingCharacters);
	text = app::utility::removeLeadingCharacter(text, leadingCharacters);
	return text;
}
