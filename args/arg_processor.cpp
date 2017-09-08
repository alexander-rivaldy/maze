#include "arg_processor.h"
//array of valid argument strings that can be passed in from the 
//command line
const std::string arg_processor::arg_strings[arg_processor::NUM_OPTIONS]
= {"--ga", "--ge", "--sv", "--sb", "--lb", "--pm","--pe","--pb","--pd"};

/**
 * constructor - simply copies the arguments passed in from the command line
 * into a vector for later processing
 **/
arg_processor::arg_processor( int argc, char*argv[])
{
    int count;
    for(count = 1; count < argc; ++count)
    {
        arguments.push_back(argv[count]);
    }
}

/**
 * processes all command line arguments that were passed into the 
 * constructor
 **/
std::vector <std::unique_ptr < action > > arg_processor::process(void)
{
    //count of the arguments that have been processed
    int arg_count, 
        //count of the option values we have iterated over 
        opt_count;
    int size = arguments.size();
    //iterate over each argument in the arguments vector
    for(arg_count = 0; arg_count < size; ++arg_count)
    {
        bool processed;
        processed=false;
        //iterate over each option in the arg_strings vector
        for(opt_count = 0; opt_count < NUM_OPTIONS; ++opt_count)
        {
            //if they are the same
            if(arguments[arg_count] == arg_strings[opt_count])
            {
                processed=true;
                //increment the count of arguments as we have just 
                //processed one.
                ++arg_count;
                //which option type are we processing?
                option_type type = option_type(opt_count);
                //if we are not generating, there should be one argument
                //for the option
                if(type != option_type::GENERATE_AB && type != option_type::GENERATE_ELLER)
                {
                    int distance = find_next_option(arguments, arg_count);
                    if(distance != ONE_ARGUMENT)
                    {
                        std::ostringstream oss;
                        oss << "Error: You did not specify correct "
                            << "arguments for the " 
                            << arguments[arg_count-1] << "action."
                            << std::endl;
                        throw action_failed(oss.str());
                    }
                }
                std::unique_ptr<action> newact;
                switch (type)
                {
                    case option_type::GENERATE_AB:
					case option_type::GENERATE_ELLER:
                        {
                            //a generate action was requested - we 
                            //implement this processing in a different
                            //function
                            newact=process_generate_argument(arg_count,
                                    false);
                            //need to move the unique_ptr onto the vector
                            //as it is a move only type
                            actions.push_back(std::move(newact));
                        }
                        break;
                    case option_type::SAVE_VECTOR:
                        {
                            std::string name = arguments[arg_count];
                            if(name.size() < EXTLEN 
                                    || (name.compare(name.size()-EXTLEN,
                                            EXTLEN, ".svg") 
                                        && name.compare(name.size()-EXTLEN,
                                            EXTLEN,".SVG")))
                            {
                                throw action_failed("svg files must have "
                                        "a .svg extension");
                            }
                            //create a save action that will store
                            //this request
                            std::unique_ptr<action> newact 
                                = std::make_unique<save_action>
                                (save_type::SVG, arguments[arg_count]);
                            actions.push_back(std::move(newact));
                        }
                        break;
                    case option_type::SAVE_BINARY:
                        {
                            //create a save action that will store this
                            //request
                            std::unique_ptr<action> newact
                                = std::make_unique<save_action>
                                (save_type::BINARY, arguments[arg_count]);
                            actions.push_back(std::move(newact));
                        }
                        break;
                    case option_type::LOAD_BINARY:
                        {
                            //create a load action that will store
                            //this request
                            std::unique_ptr<action> newact
                                = std::make_unique<load_action>
                                (arguments[arg_count]);
                            actions.push_back(std::move(newact));
                        }
                        break;
					case option_type::SOLVE_MANHATTAN:
						{
                            std::string name = arguments[arg_count];
                            if(name.size() < EXTLEN 
                                    || (name.compare(name.size()-EXTLEN,
                                            EXTLEN, ".svg") 
                                        && name.compare(name.size()-EXTLEN,
                                            EXTLEN,".SVG")))
                            {
                                throw action_failed("svg files must have "
                                        "a .svg extension");
                            }
                            //create a save action that will store
                            //this request
                            std::unique_ptr<action> newact 
                                = std::make_unique<solve_action>
                                (solve_type::DIJKSTRA_MANHATTAN, arguments[arg_count]);
                            actions.push_back(std::move(newact));
						}
					break;
					case option_type::SOLVE_EUCLIDEAN:
						{
							std::string name = arguments[arg_count];
                            if(name.size() < EXTLEN 
                                    || (name.compare(name.size()-EXTLEN,
                                            EXTLEN, ".svg") 
                                        && name.compare(name.size()-EXTLEN,
                                            EXTLEN,".SVG")))
                            {
                                throw action_failed("svg files must have "
                                        "a .svg extension");
                            }
                            //create a save action that will store
                            //this request
                            std::unique_ptr<action> newact 
                                = std::make_unique<solve_action>
                                (solve_type::DIJKSTRA_EUCLIDEAN, arguments[arg_count]);
                            actions.push_back(std::move(newact));
						}
					break;
					case option_type::SOLVE_BREADTH:
						{
							std::string name = arguments[arg_count];
                            if(name.size() < EXTLEN 
                                    || (name.compare(name.size()-EXTLEN,
                                            EXTLEN, ".svg") 
                                        && name.compare(name.size()-EXTLEN,
                                            EXTLEN,".SVG")))
                            {
                                throw action_failed("svg files must have "
                                        "a .svg extension");
                            }
                            //create a save action that will store
                            //this request
                            std::unique_ptr<action> newact 
                                = std::make_unique<solve_action>
                                (solve_type::BREADTH, arguments[arg_count]);
                            actions.push_back(std::move(newact));
						}
					break;
					case option_type::SOLVE_DEPTH:
						{
							std::string name = arguments[arg_count];
                            if(name.size() < EXTLEN 
                                    || (name.compare(name.size()-EXTLEN,
                                            EXTLEN, ".svg") 
                                        && name.compare(name.size()-EXTLEN,
                                            EXTLEN,".SVG")))
                            {
                                throw action_failed("svg files must have "
                                        "a .svg extension");
                            }
                            //create a save action that will store
                            //this request
                            std::unique_ptr<action> newact 
                                = std::make_unique<solve_action>
                                (solve_type::DEPTH, arguments[arg_count]);
                            actions.push_back(std::move(newact));
						}
					break;
                }
                break;
            }
            //test whether we have processed the current argument
            //if we have not then it is an invalid argument
            if(arg_count >= size-1 && processed)
                break;
        }
        if(!processed)
            throw action_failed("invalid argument passed in from the"
                    " command line");
    }

    return std::move(actions);
}

    std::string option_string
(option_type type)
{
    switch(type)
    {
        case option_type::GENERATE_AB:
            return "generate with albus broder algorithm";
            break;
		case option_type::GENERATE_ELLER:
			return "generate with Eller's algorithm";
			break;
        case option_type::SAVE_VECTOR:
            return "save vector";
            break;
        case option_type::SAVE_BINARY:
            return "save binary";
            break;
        case option_type::LOAD_BINARY:
            return "load binary";
            break;
		case option_type::SOLVE_MANHATTAN:
            return "solve maze with Djikstra algorithm, manhattan ";
            break;
		case option_type::SOLVE_EUCLIDEAN:
            return "solve maze with Djikstra algorithm, euclidean ";
            break;
		case option_type::SOLVE_BREADTH:
            return "solve maze with breadth first search";
            break;
		case option_type::SOLVE_DEPTH:
            return "solve maze with depth first search";
            break;
    }
    return "Invalid";
}

/**
 * finds the next option argument (one with --) for processing in order
 * to evaluate variable arguments for an option
 **/
int arg_processor::find_next_option(
        const std::vector<std::string> args, const int cur_arg)
{
    //store the index of the current argument
    int count = cur_arg;
    //constant for telling string comparison to compare the first two
    //characters
    const int FIRSTTWO=2;
    //iterate over the args vector starting at cur_arg until we find
    //an option argument
    for(auto it = args.begin()+cur_arg; it != args.end(); ++it, ++count)
    {
        //is this an option argument?
        if(it->compare(0,FIRSTTWO,"--") == 0)
            return count - cur_arg;
    }
    //if we have reached the end of the vector, just return a count of 
    //how far we have gotten
    return count - cur_arg;
}


bool arg_processor::valid_dim(int val)
{
    if(val < MINDIM || val > MAXDIM)
        return false;
    return true;
}


/**
 * handles the processing of a generate argument. Moved into a separate
 * function as it is a fairly complex process that was better moved to a 
 * separate function
 **/
    std::unique_ptr<action> arg_processor::process_generate_argument(
        int& arg_count, bool use_stack)
{
    //this function returns a std::unique_ptr so that the memory will be
    //freed when it goes out of scope
    std::unique_ptr<action>newact;

    //as generate actions require a variable number
    //of arguments, we need to see how many 
    //arguments there are and this will be 
    //calculated in the find_next_option() function
    int distance = 
        find_next_option(arguments,arg_count);
    int width, height;
    long seed;
    //different distances indicate different types of generate requests
    generate_type type=generate_type(distance);
    switch(type)
    {
        case generate_type::DEFAULT:
            {
                //set all values to default values as none were specified
                seed=ERROR;
                width=DEFAULT_WIDTH;
                height=DEFAULT_HEIGHT;
                break;
            }
        case generate_type::NODIMS:
            {
                width=DEFAULT_WIDTH;
                height=DEFAULT_HEIGHT;
                try
                {
                    std::size_t pos;
                    seed = stol(arguments[arg_count], &pos);
                    if(pos != std::string(arguments[arg_count]).size())
                    {
                        throw std::invalid_argument("seed is not numeric"); 
                    }
                }
                catch(std::invalid_argument& inval)
                {
                    std::ostringstream oss;
                    oss << "You specified an invalid seed value" 
                        << std::endl;
                    throw action_failed(oss.str());
                }

                break;
            }
        case generate_type::NOSEED:
            {
                //no seed was provided so we will 
                //have to generate one later
                seed = ERROR;
                try
                {
                    //two arguments left to process
                    //let's do that.
                    std::size_t pos;
                    width = 
                        stoi(arguments[arg_count++], &pos);
                    if(pos != std::string(arguments[arg_count - 1])
                        .size())
                    {
                        throw std::invalid_argument("invalid width");
                    }
                    height = 
                        stoi(arguments[arg_count], &pos);
                    if(pos != std::string(arguments[arg_count]).size())
                    {
                        throw std::invalid_argument("invalid height");
                    }
                }
                catch(std::invalid_argument & inval)
                {
                    //validate that actual integers were passed in
                    std::ostringstream oss;
                    oss << "You did not pass in valid integers for " 
                        << "generation of a maze" << std::endl;
                    throw(action_failed(oss.str()));
                }
                //we need to validate that these are 
                //values within the range of valid widths 
                // / heights
                if(!valid_dim(width) || !valid_dim(height))
                {
                    std::string message = 
                        "the dimension provided for a maze"
                        " are out of range";
                    throw action_failed(message);
                }
                break;
            }
        case generate_type::ALLSPEC:
            {

                //in this case, the seed has been provided
                //so we will capture it along with the 
                //width and height
                try
                {
                    std::size_t pos;

                    seed = stol(arguments[arg_count++], &pos);
                    if(pos != std::string(arguments[arg_count-1]).size())
                    {
                        throw std::invalid_argument("invalid seed");
                    }
                    width = stoi(arguments[arg_count++], &pos);
                    if(pos != std::string(arguments[arg_count-1]).size())
                    {
                        throw std::invalid_argument("invalid width");
                    }
                    height = stoi(arguments[arg_count], &pos);
                    if(pos != std::string(arguments[arg_count]).size())
                    {
                        throw std::invalid_argument("invalid height");
                    }
                }
                catch(std::invalid_argument & inval)
                {
                    //oops we got some invalid input so let's deal 
                    //with that
                    std::ostringstream oss;
                    oss << "You did not pass in valid integers into "
                        << "a generation request." << std::endl;
                    throw action_failed(oss.str());
                }
                break;
            }
        default:
            {
                //an invalid action was requested - due to how this
                //function has been written, this should never be run -
                //it is mainly here to remove a compiler warning
                throw action_failed("invalid generation request");
            }
    }
	bool ellerAlgorithm = false;
	if(arguments[0] == "--ge")
		ellerAlgorithm = true;
    newact=std::make_unique<generate_action>(seed, width, height, ellerAlgorithm);
    return std::move(newact);
}
