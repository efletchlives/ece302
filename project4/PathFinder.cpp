#include "PathFinder.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

PathFinder::PathFinder(const Image<Pixel> &img)
{
    load(img);
} // Constructor delegates to load() function

void PathFinder::load(const Image<Pixel> &img)
{
    // use try catch to check if image is valid
    //try {
    checkImage(img);
    //} catch (const std::invalid_argument) {}
    image = img;

    int row = img.height();
    int col = img.width();

    // find start point
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(img(i,j) == RED) {
                start_pt = {i,j};
            }
        }
    }
}

PathFinder::~PathFinder()
{
    clear();
} // Destructor delegates to clear() function

void PathFinder::checkImage(const Image<Pixel> &img)
{
    int row = img.height(); // stores the number of pixels in a row
    int col = img.width(); // stores the number of pixels in a column
    int count_red = 0; // counts red pixels

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Pixel pix = img(i,j);

            if (pix == RED) {
                count_red++;
            }
            // if pixels are any color other than white, black, or red
            else if (pix != BLACK && pix != WHITE && pix != RED) {
                throw std::invalid_argument("invalid pixel color in image");
            }

            // checking for out of bounds part: test #5 debugging
            // std::cout << i << ", " << j << std::endl;
        }
    }
    // if there are no red images or more than one red image
    if(count_red == 0 || count_red > 1) {
        throw std::invalid_argument("no red pixels or more than one red pixel in image");
    }
}

void PathFinder::findPath(std::string strategy)
{

    Queue<Coord,List<Coord>> unexplored; // queue that stores what you are going to explore
    std::vector<std::vector<int>> explored(image.height(), std::vector<int>(image.width(), 0)); // container to store the explored states (set coordinate to '1' when explored)

    // for coloring the path
    std::vector<std::vector<Coord>> parents(image.height(), std::vector<Coord>(image.width(), {-1,-1})); // container to store parents (set them to invalid to catch when you go out of bounds)
    
    unexplored.enqueue(start_pt);
    explored[start_pt.row][start_pt.col] = 1;
    Coord curr_coords = start_pt; // set to starting position


    while(!unexplored.isEmpty()) {
            curr_coords = unexplored.peekFront(); // to store current coordinates
            unexplored.dequeue(); // remove current coord from unexplored

            if (curr_coords.row == 0 || curr_coords.col == 0 || curr_coords.row == image.height() - 1 || curr_coords.col == image.width() - 1) {
                end_pt = curr_coords; // set the end point to the current coord
                image(curr_coords.row,curr_coords.col) = GREEN; // set the goal coord to green

                // to color the path yellow
                Coord path_color = end_pt;
                
                // until it reaches the start
                while(path_color != start_pt) {

                    Coord parent = parents[path_color.row][path_color.col];

                    // if the parent coordinate is invalid
                    if(parent == Coord{-1,-1}) {
                        throw std::runtime_error("parents link back to start point is incomplete");
                    }
                    // this is added to make sure you don't color over the red pixel
                    if(parent != start_pt) {
                        image(parent.row,parent.col) = YELLOW; // color pixel in path yellow
                    }

                    path_color = parent;
                }

                return; // exit out of the function because you did what you wanted to
            }

        for (int i = 0; i < 4; i++) {
            std::string::iterator strategy_iter = strategy.begin() + i; // to iterate through the strategy string
            Coord coords = curr_coords;

            // switch case to handle the different strategies as input
            switch (*strategy_iter) {
                case 'N': // north
                    coords.row--; // goes to coord north of current coord
                    break;
                case 'S': // south
                    coords.row++; // goes to coord south of current coord
                    break;
                case 'W': // west
                    coords.col--; // goes to coord west of current coord
                    break;
                case 'E': // east
                    coords.col++; // goes to coord east of current coord
                    break;
            }


            // making sure its in bounds
            if(coords.row < 0 && coords.row >= image.height() && coords.col < 0 && coords.col >= image.width()) {
                continue;
            }
            
            // check if it hasn't been explored and that it is a white pix
            if (explored[coords.row][coords.col] == 0 && image(coords.row, coords.col) == WHITE) {
                explored[coords.row][coords.col] = 1;

                // for debugging
                // std::cout << coords.row << ", " << coords.col << std::endl;

                parents[coords.row][coords.col] = curr_coords; // add current coordinates as a parent since it has a child
                unexplored.enqueue(coords); // add this new position to the queue
            }
            
            // go back up to top of for loop
        } // end of strategy implementation
    }

    throw std::runtime_error("path not found"); // if path cannot be found
}


void PathFinder::findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, std::string strategy)
{
    // frame_duration and frame_gap should stay the same throughout the function
    // initialize counter for checking against frame_gap
    int gap_check = 0; // same as frame duration

    // Initialize GIF writer
    int cell_size = 1; // Each cell is 1x1 pixels, you can change this to a larger size if needed
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    GifWriter gif; // a gif object has been declared and is pending for writing
    if (!GifBegin(&gif, (outfile + ".gif").c_str(), gif_width, gif_height, frame_duration, 8, true))
    {
        throw std::runtime_error("Failed to create GIF file.");
    }


    Queue<Coord,List<Coord>> unexplored; // queue that stores what you are going to explore
    std::vector<std::vector<int>> explored(image.height(), std::vector<int>(image.width(), 0)); // container to store the explored states (set coordinate to '1' when explored)

    // for coloring the path
    std::vector<std::vector<Coord>> parents(image.height(), std::vector<Coord>(image.width(), {-1,-1})); // container to store parents (set them to invalid to catch when you go out of bounds)
    
    unexplored.enqueue(start_pt);
    explored[start_pt.row][start_pt.col] = 1;
    Coord curr_coords = start_pt; // set to starting position


    while(!unexplored.isEmpty()) {
            curr_coords = unexplored.peekFront(); // to store current coordinates
            unexplored.dequeue(); // remove current coord from unexplored

            if (curr_coords.row == 0 || curr_coords.col == 0 || curr_coords.row == image.height() - 1 || curr_coords.col == image.width() - 1) {
                end_pt = curr_coords; // set the end point to the current coord

                //image(curr_coords.row,curr_coords.col) = GREEN; // set the goal coord to green

                // to color the path yellow
                Coord path_color = end_pt;
                
                // until it reaches the start
                while(path_color != start_pt) {

                    Coord parent = parents[path_color.row][path_color.col];

                    // if the parent coordinate is invalid
                    if(parent == Coord{-1,-1}) {
                        throw std::runtime_error("parents link back to start point is incomplete");
                    }
                    // this is added to make sure you don't color over the red pixel
                    if(parent != start_pt) {
                        image(parent.row,parent.col) = YELLOW; // color pixel in path yellow
                    }

                    path_color = parent;
                }
                addFrameToGif(gif,frame_duration); // add frame for yellow
                
                GifEnd(&gif); // return gif 
                return; // exit out of the function because you did what you wanted to
            }

        for (int i = 0; i < 4; i++) {
            std::string::iterator strategy_iter = strategy.begin() + i; // to iterate through the strategy string
            Coord coords = curr_coords;

            // switch case to handle the different strategies as input
            switch (*strategy_iter) {
                case 'N': // north
                    coords.row--; // goes to coord north of current coord
                    break;
                case 'S': // south
                    coords.row++; // goes to coord south of current coord
                    break;
                case 'W': // west
                    coords.col--; // goes to coord west of current coord
                    break;
                case 'E': // east
                    coords.col++; // goes to coord east of current coord
                    break;
            }

            // set goal point color to green
            if (curr_coords.row == 0 || curr_coords.col == 0 || curr_coords.row == image.height() - 1 || curr_coords.col == image.width() - 1) {
                image(coords.row, coords.col) = GREEN;
                addFrameToGif(gif,frame_duration);
                gap_check = 0;
                break; // breaks out of for loop
            }

            // check if it hasn't been explored and that it is a white pix
            else if (explored[coords.row][coords.col] == 0 && image(coords.row, coords.col) == WHITE) {
                explored[coords.row][coords.col] = 1;

                // set the found pix to blue 
                image(coords.row, coords.col) = BLUE;

                // for debugging
                // std::cout << coords.row << ", " << coords.col << std::endl;

                parents[coords.row][coords.col] = curr_coords; // add current coordinates as a parent since it has a child
                unexplored.enqueue(coords); // add this new position to the queue

                gap_check++; // increment the gap

                // check for if the amount of steps passed is equal to the frame gap specified
                if(gap_check == frame_gap) {
                    addFrameToGif(gif,frame_duration);
                    gap_check = 0; // reset the frame duration
                }
            }
            
            // go back up to top of for loop
        } // end of strategy implementation
    }

    throw std::runtime_error("path not found"); // if path cannot be found
    
    
    // TODO, strategy is default at "NSWE"
    // Must use Queue ADT to implement BFS algorithm with visualization

    // Must use `` addFrameToGif(gif, frame_duration) `` at certain time to write the frame to the gif
    // Before each of your function exit (e.g., return or throw), you have to conclude the gif object
    // by `` GifEnd(&gif); ``

    // It's also expected to have
    // ``writeToFile(image, outfile + "_final_visual.png")`` at the end of pathfinding
    
}

// Helper function
void PathFinder::addFrameToGif(GifWriter &gif, int frame_duration)
{
    // Each coordinate is 1x1 pixels, you can change this to a larger size if needed
    int cell_size = 1;
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;
    // 4 is the number of channels (RGBA)
    std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

    // Convert the image to RGB format for the GIF
    for (int r = 0; r < image.height(); ++r)
    {
        for (int c = 0; c < image.width(); ++c)
        {
            Pixel color;
            if (image(r, c) == WHITE)
            {
                color = {255, 255, 255};
            }
            else if (image(r, c) == BLACK)
            {
                color = {0, 0, 0};
            }
            else if (image(r, c) == RED)
            {
                color = {255, 0, 0};
            }
            else if (image(r, c) == GREEN)
            {
                color = {0, 255, 0};
            }
            else if (image(r, c) == BLUE)
            {
                color = {0, 0, 255};
            }
            else if (image(r, c) == YELLOW)
            {
                color = {255, 255, 0};
            }
            else
            {
                color = {0, 0, 0};
            }

            // Fill the cell with the color
            for (int i = 0; i < cell_size; ++i)
            {
                for (int j = 0; j < cell_size; ++j)
                {
                    int pixel_row = r * cell_size + i;
                    int pixel_col = c * cell_size + j;
                    int index = (pixel_row * gif_width + pixel_col) * 4;
                    rgb_data[index + 0] = color.red;
                    rgb_data[index + 1] = color.green;
                    rgb_data[index + 2] = color.blue;
                    rgb_data[index + 3] = 255; // Alpha channel
                }
            }
        }
    }
    // Write the frame to the GIF
    GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // Finished

void PathFinder::writeSolutionToFile(const std::string &filename)
{
    writeToFile(image, filename);
} // delegate to writeToFile function in lib/image.h

// gets position of red pixel
Coord PathFinder::getStart()
{
    return start_pt; // returns the start point (location of red pixel)
}

Coord PathFinder::getEnd()
{
    return end_pt; // end_pt is the green pixel (goal pixel)
}

// clear the image, idk how to do this yet
void PathFinder::clear()
{
    image = Image<Pixel>();

    start_pt = {-1,-1};
    next_state = {-1,-1};
    end_pt = {-1,-1};
}

// Nonmember functions
bool compareImagesExit(std::string img1_str, std::string img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            // Check if the pixels are different and one of them is GREEN
            if (img1(r, c) != img2(r, c) && (img1(r, c) == GREEN || img2(r, c) == GREEN))
            {
                return false;
            }
        }
    }
    return true;
} // Finished

bool compareImages(std::string img1_str, std::string img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c))
            {
                return false;
            }
        }
    }
    return true;
} // Finished