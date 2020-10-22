#include <iostream>
#include <string>
#include "pyhelper.hpp"
#include "utils.hpp"

/**
 * Wrapper methods for the openrouteservice python script.
 */
namespace apicaller::openroute {
    /**
     * Fetches a many-to-many distance and duration matrix from the openrouteservice api.
     * 
     * @param locations A JSON string representation of locations (format="[[<lon>,<lat>],...]").
     * @param profile [optional] The transportation profile to use (default="foot-walking").
     * @return JSON string with the API result.
     */
    std::string matrix(std::string locations, std::string profile = "foot-walking");

    /**
     * Fetches a one-to-many distance and duration matrix from the openrouteservice api.
     * 
     * @param locations A JSON string representation of locations (format="[[<lon>,<lat>],...]").
     * @param profile [optional] The transportation profile to use (default="foot-walking").
     * @return JSON string with the API result.
     */
    std::string matrixOTM(std::string locations, int sourceIndex, std::string profile = "foot-walking");

    /**
     * Fetches a many-to-one distance and duration matrix from the openrouteservice api.
     * 
     * @param locations A JSON string representation of locations (format="[[<lon>,<lat>],...]").
     * @param profile [optional] The transportation profile to use (default="foot-walking").
     * @return JSON string with the API result.
     */
    std::string matrixMTO(std::string locations, int destinationIndex, std::string profile = "foot-walking");
}