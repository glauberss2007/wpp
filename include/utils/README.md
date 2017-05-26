# Utility functions for C++

This is a list of the functions we still have to implement.

Ideas from [MATLAB](https://www.mathworks.com/help/matlab/functionlist.html) and [Armadillo](http://arma.sourceforge.net/docs.html).

# Functions

## Language Fundamentals

### Entering Commands

`ans`: Most recent answer

`clc`: Clear Command Window

`diary`: Save Command Window text to file

`format`: Set Command Window output display format

`home`: Send cursor home

`iskeyword`: Determine whether input is MATLAB keyword

`more`: Control paged output for Command Window

### Matrices and Arrays

`zeros`: Create array of all zeros

`ones`: Create array of all ones

`rand`: Uniformly distributed random numbers

`true`: Logical 1 (true)

`false`: Logical 0 (false)

`eye`: Identity matrix

`diag`: Create diagonal matrix or get diagonal elements of matrix

`blkdiag`: Construct block diagonal matrix from input arguments

`cat`: Concatenate arrays along specified dimension

`horzcat`: Concatenate arrays horizontally

`vertcat`: Concatenate arrays vertically

`repelem`: Repeat copies of array elements

`repmat`: Repeat copies of array

`linspace`: Generate linearly spaced vector

`logspace`: Generate logarithmically spaced vector

`freqspace`: Frequency spacing for frequency response

`meshgrid`: 2-D and 3-D grids

`ndgrid`: Rectangular grid in N-D space

`length`: Length of largest array dimension

`size`: Array size

`ndims`: Number of array dimensions

`numel`: Number of array elements

`isscalar`: Determine whether input is scalar

`isvector`: Determine whether input is vector

`ismatrix`: Determine whether input is matrix

`isrow`: Determine whether input is row vector

`iscolumn`: Determine whether input is column vector

`isempty`: Determine whether array is empty

`sort`: Sort array elements

`sortrows`: Sort rows of array, table, or timetable

`issorted`: Determine whether array is sorted

`flip`: Flip order of elements

`fliplr`: Flip array left to right

`flipud`: Flip array up to down

`rot90`: Rotate array 90 degrees

`transpose`: Transpose vector or matrix

`ctranspose`: Complex conjugate transpose

`permute`: Rearrange dimensions of N-D array

`ipermute`: Inverse permute dimensions of N-D array

`circshift`: Shift array circularly

`shiftdim`: Shift dimensions

`reshape`: Reshape array

`squeeze`: Remove singleton dimensions

`colon`: Create vectors, array subscripting, and for-loop iterators

`end`: Terminate block of code, or indicate last array index

`ind2sub`: Subscripts from linear index

`sub2ind`: Convert subscripts to linear indices

### Operators and Elementary Operations

####  Arithmetic

`plus`: Addition

`uplus`: Unary plus

`minus`: Subtraction

`uminus`: Unary minus

`times`: Element-wise multiplication

`rdivide`: Right array division

`ldivide`: Left array division

`power`: Element-wise power

`mtimes`: Matrix Multiplication

`mrdivide`: Solve systems of linear equations xA = B for x

`mldivide`: Solve systems of linear equations Ax = B for x

`mpower`: Matrix power

`cumprod`: Cumulative product

`cumsum`: Cumulative sum

`diff`: Differences and Approximate Derivatives

`movsum`: Moving sum

`prod`: Product of array elements

`sum`: Sum of array elements

`ceil`: Round toward positive infinity

`fix`: Round toward zero

`floor`: Round toward negative infinity

`idivide`: Integer division with rounding option

`mod`: Remainder after division (modulo operation)

`rem`: Remainder after division

`round`: Round to nearest decimal or integer

`bsxfun`: Apply element-wise operation to two arrays with implicit expansion enabled

####  Relational Operations

`eq`: Determine equality

`ge`: Determine greater than or equal to

`gt`: Determine greater than

`le`: Determine less than or equal to

`lt`: Determine less than

`ne`: Determine inequality

`isequal`: Determine array equality

`isequaln`: Determine array equality, treating NaN values as equal

####  Logical Operations

`Logical Operators: Short-circuit`: Logical operations with short-circuiting

`and`: Find logical AND

`not`: Find logical NOT

`or`: Find logical OR

`xor`: Find logical exclusive-OR

`all`: Determine if all array elements are nonzero or true

`any`: Determine if any array elements are nonzero

`false`: Logical 0 (false)

`find`: Find indices and values of nonzero elements

`islogical`: Determine if input is logical array

`logical`: Convert numeric values to logicals

`true`: Logical 1 (true)

####  Set Operations

`intersect`: Set intersection of two arrays

`ismember`: Array elements that are members of set array

`ismembertol`: Members of set within tolerance

`issorted`: Determine whether array is sorted

`setdiff`: Set difference of two arrays

`setxor`: Set exclusive OR of two arrays

`union`: Set union of two arrays

`unique`: Unique values in array

`uniquetol`: Unique values within tolerance

`join`: Combine strings, or merge two tables or timetables by rows using key variables

`innerjoin`: Inner join between two tables or two timetables

`outerjoin`: Outer join between two tables or two timetables

####  Bit-Wise Operations

`bitand`: Bit-wise AND

`bitcmp`: Bit-wise complement

`bitget`: Get bit at specified position

`bitor`: Bit-wise OR

`bitset`: Set bit at specific location

`bitshift`: Shift bits specified number of places

`bitxor`: Bit-wise XOR

`swapbytes`: Swap byte ordering

### Special Characters

`Special Characters`: Special characters

`colon`: Create vectors, array subscripting, and for-loop iterators

### Data Types

####  Numeric Types

`double`: Convert to double precision

`single`: Convert to single precision

`int8`: Convert to 8-bit signed integer

`int16`: Convert to 16-bit signed integer

`int32`: Convert to 32-bit signed integer

`int64`: Convert to 64-bit signed integer

`uint8`: Convert to 8-bit unsigned integer

`uint16`: Convert to 16-bit unsigned integer

`uint32`: Convert to 32-bit unsigned integer

`uint64`: Convert to 64-bit unsigned integer

`cast`: Cast variable to different data type

`typecast`: Convert data types without changing underlying data

`isinteger`: Determine if input is integer array

`isfloat`: Determine if input is floating-point array

`isnumeric`: Determine if input is numeric array

`isreal`: Determine whether array is real

`isfinite`: Array elements that are finite

`isinf`: Array elements that are infinite

`isnan`: Array elements that are NaN

`eps`: Floating-point relative accuracy

`flintmax`: Largest consecutive integer in floating-point format

`Inf`: Infinity

`intmax`: Largest value of specified integer type

`intmin`: Smallest value of specified integer type

`NaN`: Not-a-Number

`realmax`: Largest positive floating-point number

`realmin`: Smallest positive normalized floating-point number

####  Characters and Strings

`string`: Create string array

`strings`: Create array of strings with no characters

`join`: Combine strings, or merge two tables or timetables by rows using key variables

`char`: Convert to character array

`cellstr`: Convert to cell array of character vectors

`blanks`: Create character array of blanks

`newline`: Create newline character

`compose`: Convert data into formatted string array

`sprintf`: Format data into string

`strcat`: Concatenate strings horizontally

`ischar`: Determine if item is character array

`iscellstr`: Determine if input is cell array of character vectors

`isstring`: Determine if input is string array

`strlength`: Length of strings in string array

`isstrprop`: Determine if string is of specified category

`isletter`: Array elements that are alphabetic letters

`isspace`: Array elements that are space characters

`symvar`: Determine symbolic variables in expression

`contains`: Determine if pattern is in string

`count`: Count occurrences of pattern in string

`endsWith`: Determine if string ends with pattern

`startsWith`: Determine if string starts with pattern

`strfind`: Find one string within another

`sscanf`: Read formatted data from string

`replace`: Find and replace substrings in string array

`replaceBetween`: Replace substrings identified by indicators that mark their starts and ends

`strrep`: Find and replace substring

`join`: Combine strings, or merge two tables or timetables by rows using key variables

`split`: Split strings in string array, or split calendar duration into numeric and duration units

`splitlines`: Split string at newline characters

`strjoin`: Join text in array

`strsplit`: Split string at specified delimiter

`strtok`: Selected parts of string

`erase`: Delete substrings within strings

`eraseBetween`: Delete substrings between indicators that mark starts and ends of substrings

`extractAfter`: Extract substring after specified position

`extractBefore`: Extract substring before specified position

`extractBetween`: Extract substrings between indicators that mark starts and ends of substrings

`insertAfter`: Insert string after specified substring

`insertBefore`: Insert string before specified substring

`pad`: Add leading or trailing characters to strings

`strip`: Remove leading and trailing characters from string

`lower`: Convert string to lowercase

`upper`: Convert string to uppercase

`reverse`: Reverse order of characters in string

`deblank`: Remove trailing whitespace from end of string or character array

`strtrim`: Remove leading and trailing whitespace from string array or character array

`strjust`: Justify string or character array

`strcmp`: Compare strings

`strcmpi`: Compare strings (case insensitive)

`strncmp`: Compare first n characters of strings
(case sensitive)

`strncmpi`: Compare first n characters of strings
(case insensitive)

`regexp`: Match regular expression (case sensitive)

`regexpi`: Match regular expression (case insensitive)

`regexprep`: Replace text using regular expression

`regexptranslate`: Translate text into regular expression

####  Dates and Time

##### Create Date and Time Arrays

`datetime`: Create array based on current date, or convert from date strings or numbers

`timezones`: List time zones

`years`: Duration in years

`days`: Duration in days

`hours`: Duration in hours

`minutes`: Duration in minutes

`seconds`: Duration in seconds

`milliseconds`: Duration in milliseconds

`duration`: Create duration array from numeric values

`calyears`: Calendar duration in years

`calquarters`: Calendar duration in quarters

`calmonths`: Calendar duration in months

`calweeks`: Calendar duration in weeks

`caldays`: Calendar duration in days

`calendarDuration`: Create calendar duration array from numeric values

`exceltime`: Convert MATLAB datetime to Excel date number

`juliandate`: Convert MATLAB datetime to Julian date

`posixtime`: Convert MATLAB datetime to POSIX time

`yyyymmdd`: Convert MATLAB datetime to YYYYMMDD numeric value

##### Components of Dates and Time

`year`: Year number

`quarter`: Quarter number

`month`: Month number and name

`week`: Week number

`day`: Day number or name

`hour`: Hour number

`minute`: Minute number

`second`: Second number

`ymd`: Year, month, and day numbers of datetime

`hms`: Hour, minute, and second numbers of duration

`split`: Split strings in string array, or split calendar duration into numeric and duration units

`time`: Convert time of calendar duration to duration

`timeofday`: Elapsed time since midnight for datetimes

`isdst`: Determine daylight saving time elements

`isweekend`: Determine weekend elements

`tzoffset`: Time zone offset from UTC

##### Date and Time Arithmetic and Plotting

`between`: Calendar math differences

`caldiff`: Calendar math successive differences

`dateshift`: Shift date or generate sequence of dates and time

`isbetween`: Determine elements within date and time interval

`isdatetime`: Determine if input is datetime array

`isduration`: Determine if input is duration array

`iscalendarduration`: Determine if input is calendar duration array

`isnat`: Determine NaT (Not-a-Time) elements

`NaT`: Not-a-Time

##### Dates and Time as Numbers and Strings

`datenum`: Convert date and time to serial date number

`datevec`: Convert date and time to vector of components

`datestr`: Convert date and time to string format

`char`: Convert to character array

`cellstr`: Convert to cell array of character vectors

`now`: Current date and time as serial date number

`clock`: Current date and time as date vector

`date`: Current date string

`calendar`: Calendar for specified month

`eomday`: Last day of month

`weekday`: Day of week

`addtodate`: Modify date number by field

`etime`: Time elapsed between date vectors

####  Categorical Arrays

`categorical`: Create categorical array

`iscategorical`: Determine whether input is categorical array

`categories`: Categories of categorical array

`iscategory`: Test for categorical array categories

`isordinal`: Determine whether input is ordinal categorical array

`isprotected`: Determine whether categories of categorical array are protected

`addcats`: Add categories to categorical array

`mergecats`: Merge categories in categorical array

`removecats`: Remove categories from categorical array

`renamecats`: Rename categories in categorical array

`reordercats`: Reorder categories in categorical array

`setcats`: Set categories in categorical array

`summary`: Print summary of table, timetable, or categorical array

`countcats`: Count occurrences of categorical array elements by category

`isundefined`: Find undefined elements in categorical array

####  Tables

`table`: Create table from workspace variables

`array2table`: Convert homogeneous array to table

`cell2table`: Convert cell array to table

`struct2table`: Convert structure array to table

`table2array`: Convert table to homogeneous array

`table2cell`: Convert table to cell array

`table2struct`: Convert table to structure array

`readtable`: Create table from file

`writetable`: Write table to file

`detectImportOptions`: Create import options based on file content

`getvaropts`: Get variable import options

`setvaropts`: Set variable import options

`setvartype`: Set variable data types

`istable`: Determine whether input is table

`height`: Number of table rows

`width`: Number of table variables

`summary`: Print summary of table, timetable, or categorical array

`intersect`: Set intersection of two arrays

`ismember`: Array elements that are members of set array

`setdiff`: Set difference of two arrays

`setxor`: Set exclusive OR of two arrays

`unique`: Unique values in array

`union`: Set union of two arrays

`join`: Combine strings, or merge two tables or timetables by rows using key variables

`innerjoin`: Inner join between two tables or two timetables

`outerjoin`: Outer join between two tables or two timetables

`sortrows`: Sort rows of array, table, or timetable

`stack`: Stack data from multiple variables into single variable

`unstack`: Unstack data from single variable into multiple variables

`ismissing`: Find missing values

`standardizeMissing`: Insert standard missing-value indicators

`rmmissing`: Remove missing entries

`fillmissing`: Fill missing values

`varfun`: Apply function to table or timetable variables

`rowfun`: Apply function to table or timetable rows

`findgroups`: Find groups and return group numbers

`splitapply`: Split data into groups and apply function

####  Timetables

`timetable`: Create timetable from workspace variables

`retime`: Resample or aggregate data in timetable, and resolve duplicate or irregular times

`synchronize`: Synchronize timetables to common time vector, and resample or aggregate data from input timetables

`lag`: Time-shift data in timetable

`table2timetable`: Convert table to timetable

`array2timetable`: Convert array to timetable

`timetable2table`: Convert timetable to table

`istimetable`: Determine if input is timetable

`isregular`: Determine whether times in timetable are regular

`timerange`: Time range for timetable row subscripting

`withtol`: Time tolerance for timetable row subscripting

`vartype`: Subscript into table or timetable by variable type

`rmmissing`: Remove missing entries

`issorted`: Determine whether array is sorted

`sortrows`: Sort rows of array, table, or timetable

`unique`: Unique values in array

####  Structures

`struct`: Create structure array

`fieldnames`: Field names of structure, or public fields of COM or Java object

`getfield`: Field of structure array

`isfield`: Determine whether input is structure array field

`isstruct`: Determine whether input is structure array

`orderfields`: Order fields of structure array

`rmfield`: Remove fields from structure

`setfield`: Assign values to structure array field

`arrayfun`: Apply function to each element of array

`structfun`: Apply function to each field of scalar structure

`table2struct`: Convert table to structure array

`struct2table`: Convert structure array to table

`cell2struct`: Convert cell array to structure array

`struct2cell`: Convert structure to cell array

####  Cell Arrays

`cell`: Create cell array

`cell2mat`: Convert cell array to ordinary array of the underlying data type

`cell2struct`: Convert cell array to structure array

`cell2table`: Convert cell array to table

`celldisp`: Display cell array contents

`cellfun`: Apply function to each cell in cell array

`cellplot`: Graphically display structure of cell array

`cellstr`: Convert to cell array of character vectors

`iscell`: Determine whether input is cell array

`iscellstr`: Determine if input is cell array of character vectors

`mat2cell`: Convert array to cell array with potentially different sized cells

`num2cell`: Convert array to cell array with consistently sized cells

`strjoin`: Join text in array

`strsplit`: Split string at specified delimiter

`struct2cell`: Convert structure to cell array

`table2cell`: Convert table to cell array

####  Function Handles

`feval`: Evaluate function

`func2str`: Construct character vector from function handle

`str2func`: Construct function handle from character vector

`localfunctions`: Function handles to all local functions in MATLAB file

`functions`: Information about function handle

####  Map Containers

`containers.Map`: Map values to unique keys

`isKey`: Determine if containers.Map object contains key

`keys`: Identify keys of containers.Map object

`remove`: Remove key-value pairs from containers.Map object

`values`: Identify values in containers.Map object

####  Time Series

##### Time Series Basics

`append`: Concatenate time series objects in time dimension

`get`: Query timeseries object property values

`getdatasamplesize`: Size of data sample in timeseries object

`getqualitydesc`: Data quality descriptions

`getsamples`: Subset of time series samples using subscripted index array

`plot`: Plot time series

`set`: Set properties of timeseries object

`tsdata.event`: Construct event object for timeseries object

`timeseries`: Create timeseries object

##### Data Manipulation

`addsample`: Add data sample to timeseries object

`delsample`: Remove sample from timeseries object

`detrend`: Subtract mean or best-fit line and all NaNs from timeseries object

`filter`: Shape frequency content of time-series

`getabstime`: Extract date-string time vector into cell array

`getdatasamples`: Returns subset of time series samples using subscripted index array

`getinterpmethod`: Interpolation method for timeseries object

`getsampleusingtime`: Extract data samples into new timeseries object

`idealfilter`: Apply ideal (noncausal) filter to timeseries object

`resample`: Select or interpolate timeseries data using new time vector

`setabstime`: Set times of timeseries object as date strings

`setinterpmethod`: Set default interpolation method for timeseries object

`setuniformtime`: Modify uniform time vector of timeseries object

`synchronize`: Synchronize and resample two timeseries objects using common time vector

##### Event Data

`addevent`: Add event to timeseries object

`delevent`: Remove tsdata.event objects from timeseries object

`gettsafteratevent`: New timeseries object with samples occurring at or after event

`gettsafterevent`: New timeseries object with samples occurring after event

`gettsatevent`: New timeseries object with samples occurring at event

`gettsbeforeatevent`: New timeseries object with samples occurring before or at event

`gettsbeforeevent`: New timeseries object with samples occurring before event

`gettsbetweenevents`: New timeseries object with samples occurring between events

##### Descriptive Statistics

`iqr`: Interquartile range of timeseries data

`max`: Maximum value of timeseries data

`mean`: Mean value of timeseries data

`median`: Median value of timeseries data

`min`: Minimum value of timeseries data

`std`: Standard deviation of timeseries data

`sum`: Sum of timeseries data

`var`: Variance of timeseries data

##### Time Series Collections

`get (tscollection)`: Query tscollection object property values

`isempty (tscollection)`: Determine whether tscollection object is empty

`length (tscollection)`: Length of time vector

`plot`: Plot time series

`set (tscollection)`: Set properties of tscollection object

`size (tscollection)`: Size of tscollection object

`tscollection`: Create tscollection object

`addsampletocollection`: Add sample to tscollection object

`addts`: Add timeseries object to tscollection object

`delsamplefromcollection`: Remove sample from tscollection object

`getabstime (tscollection)`: Extract date-string time vector into cell array

`getsampleusingtime (tscollection)`: Extract data samples into new tscollection object

`gettimeseriesnames`: Cell array of names of timeseries objects in tscollection object

`horzcat (tscollection)`: Horizontal concatenation for tscollection objects

`removets`: Remove timeseries objects from tscollection object

`resample (tscollection)`: Select or interpolate data in tscollection using new time vector

`setabstime (tscollection)`: Set times of tscollection object as date strings

`settimeseriesnames`: Change name of timeseries object in tscollection

`vertcat (tscollection)`: Vertical concatenation for tscollection objects

####  Data Type Identification

`isa`: Determine if input is object of specified class

`iscalendarduration`: Determine if input is calendar duration array

`iscategorical`: Determine whether input is categorical array

`iscell`: Determine whether input is cell array

`iscellstr`: Determine if input is cell array of character vectors

`ischar`: Determine if item is character array

`isdatetime`: Determine if input is datetime array

`isduration`: Determine if input is duration array

`isfield`: Determine whether input is structure array field

`isfloat`: Determine if input is floating-point array

`isgraphics`: True for valid graphics object handles

`isinteger`: Determine if input is integer array

`isjava`: Determine if input is Java object

`islogical`: Determine if input is logical array

`isnumeric`: Determine if input is numeric array

`isobject`: Determine if input is MATLAB object

`isreal`: Determine whether array is real

`isenum`: Determine if variable is enumeration

`isstruct`: Determine whether input is structure array

`istable`: Determine whether input is table

`is*`: Detect state

`class`: Determine class of object

`validateattributes`: Check validity of array

`whos`: List variables in workspace, with sizes and types

####  Data Type Conversion

`char`: Convert to character array

`cellstr`: Convert to cell array of character vectors

`int2str`: Convert integers to character array

`mat2str`: Convert matrix to character vector

`num2str`: Convert numbers to character array

`str2double`: Convert string to double precision value

`str2num`: Convert character array to numeric array

`native2unicode`: Convert numeric bytes to Unicode character representation

`unicode2native`: Convert Unicode character representation to numeric bytes

`base2dec`: Convert text representing number in base N to decimal number

`bin2dec`: Convert text representation of binary number to decimal number

`dec2base`: Convert decimal number to character vector representing base N number

`dec2bin`: Convert decimal number to character vector representing binary number

`dec2hex`: Convert decimal number to character vector representing hexadecimal number

`hex2dec`: Convert text representation of hexadecimal number to decimal number

`hex2num`: Convert IEEE hexadecimal string to double-precision number

`num2hex`: Convert singles and doubles to IEEE hexadecimal strings

`table2array`: Convert table to homogeneous array

`table2cell`: Convert table to cell array

`table2struct`: Convert table to structure array

`array2table`: Convert homogeneous array to table

`cell2table`: Convert cell array to table

`struct2table`: Convert structure array to table

`cell2mat`: Convert cell array to ordinary array of the underlying data type

`cell2struct`: Convert cell array to structure array

`mat2cell`: Convert array to cell array with potentially different sized cells

`num2cell`: Convert array to cell array with consistently sized cells

`struct2cell`: Convert structure to cell array

## Mathematics

### Elementary Math

####  Arithmetic

`plus`: Addition

`uplus`: Unary plus

`minus`: Subtraction

`uminus`: Unary minus

`times`: Element-wise multiplication

`rdivide`: Right array division

`ldivide`: Left array division

`power`: Element-wise power

`mtimes`: Matrix Multiplication

`mrdivide`: Solve systems of linear equations xA = B for x

`mldivide`: Solve systems of linear equations Ax = B for x

`mpower`: Matrix power

`cumprod`: Cumulative product

`cumsum`: Cumulative sum

`diff`: Differences and Approximate Derivatives

`movsum`: Moving sum

`prod`: Product of array elements

`sum`: Sum of array elements

`ceil`: Round toward positive infinity

`fix`: Round toward zero

`floor`: Round toward negative infinity

`idivide`: Integer division with rounding option

`mod`: Remainder after division (modulo operation)

`rem`: Remainder after division

`round`: Round to nearest decimal or integer

`bsxfun`: Apply element-wise operation to two arrays with implicit expansion enabled

####  Trigonometry

`sin`: Sine of argument in radians

`sind`: Sine of argument in degrees

`asin`: Inverse sine in radians

`asind`: Inverse sine in degrees

`sinh`: Hyperbolic sine of argument in radians

`asinh`: Inverse hyperbolic sine

`cos`: Cosine of argument in radians

`cosd`: Cosine of argument in degrees

`acos`: Inverse cosine in radians

`acosd`: Inverse cosine in degrees

`cosh`: Hyperbolic cosine

`acosh`: Inverse hyperbolic cosine

`tan`: Tangent of argument in radians

`tand`: Tangent of argument in degrees

`atan`: Inverse tangent in radians

`atand`: Inverse tangent in degrees

`atan2`: Four-quadrant inverse tangent

`atan2d`: Four-quadrant inverse tangent in degrees

`tanh`: Hyperbolic tangent

`atanh`: Inverse hyperbolic tangent

`csc`: Cosecant of input angle in radians

`cscd`: Cosecant of argument in degrees

`acsc`: Inverse cosecant in radians

`acscd`: Inverse cosecant in degrees

`csch`: Hyperbolic cosecant

`acsch`: Inverse hyperbolic cosecant

`sec`: Secant of angle in radians

`secd`: Secant of argument in degrees

`asec`: Inverse secant in radians

`asecd`: Inverse secant in degrees

`sech`: Hyperbolic secant

`asech`: Inverse hyperbolic secant

`cot`: Cotangent of angle in radians

`cotd`: Cotangent of argument in degrees

`acot`: Inverse cotangent in radians

`acotd`: Inverse cotangent in degrees

`coth`: Hyperbolic cotangent

`acoth`: Inverse hyperbolic cotangent

`hypot`: Square root of sum of squares (hypotenuse)

`deg2rad`: Convert angle from degrees to radians

`rad2deg`: Convert angle from radians to degrees

####  Exponents and Logarithms

`exp`: Exponential

`expm1`: Compute exp(x)-1 accurately for small values of x

`log`: Natural logarithm

`log10`: Common logarithm (base 10)

`log1p`: Compute log(1+x) accurately for small values of x

`log2`: Base 2 logarithm and dissect floating-point numbers into exponent and mantissa

`nextpow2`: Exponent of next higher power of 2

`nthroot`: Real nth root of real numbers

`pow2`: Base 2 power and scale floating-point numbers

`reallog`: Natural logarithm for nonnegative real arrays

`realpow`: Array power for real-only output

`realsqrt`: Square root for nonnegative real arrays

`sqrt`: Square root

####  Complex Numbers

`abs`: Absolute value and complex magnitude

`angle`: Phase angle

`complex`: Create complex array

`conj`: Complex conjugate

`cplxpair`: Sort complex numbers into complex conjugate pairs

`i`: Imaginary unit

`imag`: Imaginary part of complex number

`isreal`: Determine whether array is real

`j`: Imaginary unit

`real`: Real part of complex number

`sign`: Sign function (signum function)

`unwrap`: Correct phase angles to produce smoother phase plots

####  Discrete Math

`factor`: Prime factors

`factorial`: Factorial of input

`gcd`: Greatest common divisor

`isprime`: Determine which array elements are prime

`lcm`: Least common multiple

`nchoosek`: Binomial coefficient or all combinations

`perms`: All possible permutations

`primes`: Prime numbers less than or equal to input value

`rat`: Rational fraction approximation

`rats`: Rational output

####  Polynomials

`poly`: Polynomial with specified roots or characteristic polynomial

`polyeig`: Polynomial eigenvalue problem

`polyfit`: Polynomial curve fitting

`residue`: Partial fraction expansion (partial fraction decomposition)

`roots`: Polynomial roots

`polyval`: Polynomial evaluation

`polyvalm`: Matrix polynomial evaluation

`conv`: Convolution and polynomial multiplication

`deconv`: Deconvolution and polynomial division

`polyint`: Polynomial integration

`polyder`: Polynomial differentiation

####  Special Functions

`airy`: Airy Functions

`besselh`: Bessel function of third kind (Hankel function)

`besseli`: Modified Bessel function of first kind

`besselj`: Bessel function of first kind

`besselk`: Modified Bessel function of second kind

`bessely`: Bessel function of second kind

`beta`: Beta function

`betainc`: Incomplete beta function

`betaincinv`: Beta inverse cumulative distribution function

`betaln`: Logarithm of beta function

`ellipj`: Jacobi elliptic functions

`ellipke`: Complete elliptic integrals of first and second kind

`erf`: Error function

`erfc`: Complementary error function

`erfcinv`: Inverse complementary error function

`erfcx`: Scaled complementary error function

`erfinv`: Inverse error function

`expint`: Exponential integral

`gamma`: Gamma function

`gammainc`: Incomplete gamma function

`gammaincinv`: Inverse incomplete gamma function

`gammaln`: Logarithm of gamma function

`legendre`: Associated Legendre functions

`psi`: Psi (polygamma) function

####  Cartesian Coordinate System Conversion

`cart2pol`: Transform Cartesian coordinates to polar or cylindrical

`cart2sph`: Transform Cartesian coordinates to spherical

`pol2cart`: Transform polar or cylindrical coordinates to Cartesian

`sph2cart`: Transform spherical coordinates to Cartesian

####  Constants and Test Matrices

`eps`: Floating-point relative accuracy

`flintmax`: Largest consecutive integer in floating-point format

`i`: Imaginary unit

`j`: Imaginary unit

`Inf`: Infinity

`pi`: Ratio of circle's circumference to its diameter

`NaN`: Not-a-Number

`isfinite`: Array elements that are finite

`isinf`: Array elements that are infinite

`isnan`: Array elements that are NaN

`compan`: Companion matrix

`gallery`: Test matrices

`hadamard`: Hadamard matrix

`hankel`: Hankel matrix

`hilb`: Hilbert matrix

`invhilb`: Inverse of Hilbert matrix

`magic`: Magic square

`pascal`: Pascal matrix

`rosser`: Classic symmetric eigenvalue test problem

`toeplitz`: Toeplitz matrix

`vander`: Vandermonde matrix

`wilkinson`: Wilkinson's eigenvalue test matrix

### Linear Algebra

`mldivide`: Solve systems of linear equations Ax = B for x

`mrdivide`: Solve systems of linear equations xA = B for x

`linsolve`: Solve linear system of equations

`inv`: Matrix inverse

`pinv`: Moore-Penrose pseudoinverse of matrix

`lscov`: Least-squares solution in presence of known covariance

`lsqnonneg`: Solve nonnegative linear least-squares problem

`sylvester`: Solve Sylvester equation AX + XB = C for X

`eig`: Eigenvalues and eigenvectors

`eigs`: Subset of eigenvalues and eigenvectors

`balance`: Diagonal scaling to improve eigenvalue accuracy

`svd`: Singular value decomposition

`svds`: Subset of singular values and vectors

`gsvd`: Generalized singular value decomposition

`ordeig`: Eigenvalues of quasitriangular matrices

`ordqz`: Reorder eigenvalues in QZ factorization

`ordschur`: Reorder eigenvalues in Schur factorization

`polyeig`: Polynomial eigenvalue problem

`qz`: QZ factorization for generalized eigenvalues

`hess`: Hessenberg form of matrix

`schur`: Schur decomposition

`rsf2csf`: Convert real Schur form to complex Schur form

`cdf2rdf`: Convert complex diagonal form to real block diagonal form

`lu`: LU matrix factorization

`ldl`: Block LDL' factorization for Hermitian indefinite matrices

`chol`: Cholesky factorization

`cholupdate`: Rank 1 update to Cholesky factorization

`qr`: Orthogonal-triangular decomposition

`qrdelete`: Remove column or row from QR factorization

`qrinsert`: Insert column or row into QR factorization

`qrupdate`: Rank 1 update to QR factorization

`planerot`: Givens plane rotation

`transpose`: Transpose vector or matrix

`ctranspose`: Complex conjugate transpose

`mtimes`: Matrix Multiplication

`mpower`: Matrix power

`sqrtm`: Matrix square root

`expm`: Matrix exponential

`logm`: Matrix logarithm

`funm`: Evaluate general matrix function

`kron`: Kronecker tensor product

`cross`: Cross product

`dot`: Dot product

`bandwidth`: Lower and upper matrix bandwidth

`tril`: Lower triangular part of matrix

`triu`: Upper triangular part of matrix

`isbanded`: Determine if matrix is within specific bandwidth

`isdiag`: Determine if matrix is diagonal

`ishermitian`: Determine if matrix is Hermitian or skew-Hermitian

`issymmetric`: Determine if matrix is symmetric or skew-symmetric

`istril`: Determine if matrix is lower triangular

`istriu`: Determine if matrix is upper triangular

`norm`: Vector and matrix norms

`normest`: 2-norm estimate

`cond`: Condition number with respect to inversion

`condest`: 1-norm condition number estimate

`rcond`: Reciprocal condition number

`condeig`: Condition number with respect to eigenvalues

`det`: Matrix determinant

`null`: Null space

`orth`: Orthonormal basis for range of matrix

`rank`: Rank of matrix

`rref`: Reduced row echelon form (Gauss-Jordan elimination)

`trace`: Sum of diagonal elements

`subspace`: Angle between two subspaces

### Random Number Generation

`rand`: Uniformly distributed random numbers

`randn`: Normally distributed random numbers

`randi`: Uniformly distributed pseudorandom integers

`randperm`: Random permutation

`rng`: Control random number generation

`RandStream`: Random number stream

### Interpolation
####  1-D Interpolation

`interp1`: 1-D data interpolation (table lookup)

`griddedInterpolant`: Gridded data interpolation

`pchip`: Piecewise Cubic Hermite Interpolating Polynomial (PCHIP)

`spline`: Cubic spline data interpolation

`ppval`: Evaluate piecewise polynomial

`mkpp`: Make piecewise polynomial

`unmkpp`: Piecewise polynomial details

`padecoef`: Padé approximation of time delays

`interpft`: 1-D interpolation using FFT method

####  Gridded Data Interpolation

`interp2`: Interpolation for 2-D gridded data in meshgrid format

`interp3`: Interpolation for 3-D gridded data in meshgrid format

`interpn`: Interpolation for 1-D, 2-D, 3-D, and N-D gridded data in ndgrid format

`griddedInterpolant`: Gridded data interpolation

`ndgrid`: Rectangular grid in N-D space

`meshgrid`: 2-D and 3-D grids

####  Scattered Data Interpolation

`griddata`: Interpolate scattered data

`griddatan`: Data gridding and hypersurface fitting (dimension ≥
2)

`scatteredInterpolant`: Scattered data interpolation

### Optimization

`fminbnd`: Find minimum of single-variable function on fixed interval

`fminsearch`: Find minimum of unconstrained multivariable function using derivative-free method

`lsqnonneg`: Solve nonnegative linear least-squares problem

`fzero`: Root of nonlinear function

`optimget`: Optimization options values

`optimset`: Create or edit optimization options structure

### Numerical Integration and Differential Equations
####  Ordinary Differential Equations

`ode45`: Solve nonstiff differential equations — medium order method

`ode23`: Solve nonstiff differential equations — low order method

`ode113`: Solve nonstiff differential equations — variable order method

`ode15s`: Solve stiff differential equations and DAEs — variable order method

`ode23s`: Solve stiff differential equations — low order method

`ode23t`: Solve moderately stiff ODEs and DAEs — trapezoidal rule

`ode23tb`: Solve stiff differential equations — trapezoidal rule + backward differentiation formula

`ode15i`: Solve fully implicit differential equations — variable order method

`decic`: Compute consistent initial conditions for ode15i

`odeget`: Extract ODE option values

`odeset`: Create or modify options structure for ODE solvers

`deval`: Evaluate differential equation solution structure

`odextend`: Extend solution to ODE

####  Boundary Value Problems

`bvp4c`: Solve boundary value problems for ordinary differential equations

`bvp5c`: Solve boundary value problems for ordinary differential equations

`bvpinit`: Form initial guess for BVP solvers

`bvpxtend`: Form guess structure for extending boundary value solutions

`bvpget`: Extract properties from options structure created with bvpset

`bvpset`: Create or alter options structure of boundary value problem

`deval`: Evaluate differential equation solution structure

####  Delay Differential Equations

`dde23`: Solve delay differential equations (DDEs) with constant delays

`ddesd`: Solve delay differential equations (DDEs) with general delays

`ddensd`: Solve delay differential equations (DDEs) of neutral type

`ddeget`: Extract properties from delay differential equations options structure

`ddeset`: Create or alter delay differential equations options structure

`deval`: Evaluate differential equation solution structure

####  Partial Differential Equations

`pdepe`: Solve initial-boundary value problems for parabolic-elliptic PDEs in 1-D

`pdeval`: Evaluate numerical solution of PDE using output of pdepe

####  Numerical Integration and Differentiation

`integral`: Numerical integration

`integral2`: Numerically evaluate double integral

`integral3`: Numerically evaluate triple integral

`quadgk`: Numerically evaluate integral, adaptive Gauss-Kronrod quadrature

`quad2d`: Numerically evaluate double integral, tiled method

`cumtrapz`: Cumulative trapezoidal numerical integration

`trapz`: Trapezoidal numerical integration

`polyint`: Polynomial integration

`del2`: Discrete Laplacian

`diff`: Differences and Approximate Derivatives

`gradient`: Numerical gradient

`polyder`: Polynomial differentiation

### Fourier Analysis and Filtering

`fft`: Fast Fourier transform

`fft2`: 2-D fast Fourier transform

`fftn`: N-D fast Fourier transform

`fftshift`: Shift zero-frequency component to center of spectrum

`fftw`: Interface to FFTW library run-time algorithm tuning control

`ifft`: Inverse fast Fourier transform

`ifft2`: 2-D inverse fast Fourier transform

`ifftn`: N-D inverse fast Fourier transform

`ifftshift`: Inverse FFT shift

`nextpow2`: Exponent of next higher power of 2

`conv`: Convolution and polynomial multiplication

`conv2`: 2-D convolution

`convn`: N-D convolution

`deconv`: Deconvolution and polynomial division

`filter`: 1-D digital filter

`filter2`: 2-D digital filter

`ss2tf`: Convert state-space representation to transfer function

### Sparse Matrices

`spalloc`: Allocate space for sparse matrix

`spdiags`: Extract and create sparse band and diagonal matrices

`speye`: Sparse identity matrix

`sprand`: Sparse uniformly distributed random matrix

`sprandn`: Sparse normally distributed random matrix

`sprandsym`: Sparse symmetric random matrix

`sparse`: Create sparse matrix

`spconvert`: Import from sparse matrix external format

`issparse`: Determine whether input is sparse

`nnz`: Number of nonzero matrix elements

`nonzeros`: Nonzero matrix elements

`nzmax`: Amount of storage allocated for nonzero matrix elements

`spfun`: Apply function to nonzero sparse matrix elements

`spones`: Replace nonzero sparse matrix elements with ones

`spparms`: Set parameters for sparse matrix routines

`spy`: Visualize sparsity pattern

`find`: Find indices and values of nonzero elements

`full`: Convert sparse matrix to full matrix

`amd`: Approximate minimum degree permutation

`colamd`: Column approximate minimum degree permutation

`colperm`: Sparse column permutation based on nonzero count

`dmperm`: Dulmage-Mendelsohn decomposition

`randperm`: Random permutation

`symamd`: Symmetric approximate minimum degree permutation

`symrcm`: Sparse reverse Cuthill-McKee ordering

`pcg`: Preconditioned conjugate gradients method

`minres`: Minimum residual method

`symmlq`: Symmetric LQ method

`gmres`: Generalized minimum residual method (with restarts)

`bicg`: Biconjugate gradients method

`bicgstab`: Biconjugate gradients stabilized method

`bicgstabl`: Biconjugate gradients stabilized (l) method

`cgs`: Conjugate gradients squared method

`qmr`: Quasi-minimal residual method

`tfqmr`: Transpose-free quasi-minimal residual method

`lsqr`: LSQR method

`ichol `: Incomplete Cholesky factorization

`ilu`: Incomplete LU factorization

`eigs`: Subset of eigenvalues and eigenvectors

`svds`: Subset of singular values and vectors

`normest`: 2-norm estimate

`condest`: 1-norm condition number estimate

`sprank`: Structural rank

`etree`: Elimination tree

`symbfact`: Symbolic factorization analysis

`spaugment`: Form least squares augmented system

`dmperm`: Dulmage-Mendelsohn decomposition

`etreeplot`: Plot elimination tree

`treelayout`: Lay out tree or forest

`treeplot`: Plot picture of tree

`gplot`: Plot nodes and links representing adjacency matrix

`unmesh`: Convert edge matrix to coordinate and Laplacian matrices

### Graph and Network Algorithms

`graph`: Create undirected graph

`digraph`: Create directed graph

`addnode`: Add new node to graph

`rmnode`: Remove node from graph

`addedge`: Add new edge to graph

`rmedge`: Remove edge from graph

`flipedge`: Reverse edge directions

`numnodes`: Number of nodes in graph

`numedges`: Number of edges in graph

`findnode`: Locate node in graph

`findedge`: Locate edge in graph

`reordernodes`: Reorder graph nodes

`subgraph`: Extract subgraph

`bfsearch`: Breadth-first graph search

`dfsearch`: Depth-first graph search

`centrality`: Measure node importance

`maxflow`: Maximum flow in graph

`conncomp`: Connected graph components

`biconncomp`: Biconnected graph components

`condensation`: Graph condensation

`bctree`: Block-cut tree graph

`minspantree`: Minimum spanning tree of graph

`toposort`: Topological order of directed acyclic graph

`isdag`: Determine if graph is acyclic

`transclosure`: Transitive closure

`transreduction`: Transitive reduction

`isisomorphic`: Determine whether two graphs are isomorphic

`isomorphism`: Compute equivalence relation between two graphs

`shortestpath`: Shortest path between two single nodes

`shortestpathtree`: Shortest path tree from node

`distances`: Shortest path distances of all node pairs

`adjacency`: Graph adjacency matrix

`incidence`: Graph incidence matrix

`laplacian`: Graph Laplacian matrix

`degree`: Degree of graph nodes

`neighbors`: Neighbors of graph node

`nearest`: Nearest neighbors within radius

`indegree`: In-degree of nodes

`outdegree`: Out-degree of nodes

`predecessors`: Node predecessors

`successors`: Node successors

`plot`: Graph plot

`labeledge`: Label graph edges

`labelnode`: Label graph nodes

`layout`: Change layout of graph plot

`highlight`: Highlight nodes and edges in plotted graph

`graph`: Graph with undirected edges

`digraph`: Graph with directed edges

`GraphPlot`: Graph plot for directed and undirected graphs

### Computational Geometry
####  Triangulation Representation

`triangulation`: Triangulation in 2-D or 3-D

`tetramesh`: Tetrahedron mesh plot

`trimesh`: Triangular mesh plot

`triplot`: 2-D triangular plot

`trisurf`: Triangular surface plot

####  Delaunay Triangulation

`delaunayTriangulation`: Delaunay triangulation in 2-D and 3-D

`delaunay`: Delaunay triangulation

`delaunayn`: N-D Delaunay triangulation

`tetramesh`: Tetrahedron mesh plot

`trimesh`: Triangular mesh plot

`triplot`: 2-D triangular plot

`trisurf`: Triangular surface plot

####  Spatial Search

`triangulation`: Triangulation in 2-D or 3-D

`delaunayTriangulation`: Delaunay triangulation in 2-D and 3-D

`dsearchn`: N-D nearest point search

`tsearchn`: N-D closest simplex search

`delaunay`: Delaunay triangulation

`delaunayn`: N-D Delaunay triangulation

####  Bounding Regions

`boundary`: Boundary of a set of points in 2-D or 3-D

`alphaShape`: Polygons and polyhedra from points in 2-D and 3-D

`convhull`: Convex hull

`convhulln`: N-D convex hull

`alphaShape`: Polygons and polyhedra from points in 2-D and 3-D

####  Voronoi Diagram

`patch`: Create one or more filled polygons

`voronoi`: Voronoi diagram

`voronoin`: N-D Voronoi diagram

####  Elementary Polygons

`polyarea`: Area of polygon

`inpolygon`: Points located inside or on edge of polygonal region

`rectint`: Rectangle intersection area

## Graphics
### 2-D and 3-D Plots
####  Line Plots

`plot`: 2-D line plot

`plot3`: 3-D line plot

`loglog`: Log-log scale plot

`semilogx`: Semilogarithmic plot

`semilogy`: Semilogarithmic plot

`errorbar`: Line plot with error bars

`fplot`: Plot expression or function

`fplot3`: 3-D parametric curve plotter

`fimplicit`: Plot implicit function

`LineSpec (Line Specification)`: Line specification

`ColorSpec (Color Specification)`: Color specification

####  Pie Charts, Bar Plots, and Histograms

`bar`: Bar graph

`bar3`: Plot 3-D bar graph

`barh`: Plot bar graph horizontally

`bar3h`: Plot horizontal 3-D bar graph

`histogram`: Histogram plot

`histcounts`: Histogram bin counts

`histogram2`: Bivariate histogram plot

`histcounts2`: Bivariate histogram bin counts

`rose`: Angle histogram plot

`pareto`: Pareto chart

`area`: Filled area 2-D plot

`pie`: Pie chart

`pie3`: 3-D pie chart

`histogram`: Histogram bar plot for numeric data

`histogram2`: Histogram bar plot for bivariate data

####  Discrete Data Plots

`stem`: Plot discrete sequence data

`stairs`: Stairstep graph

`stem3`: Plot 3-D discrete sequence data

`scatter`: Scatter plot

`scatter3`: 3-D scatter plot

`spy`: Visualize sparsity pattern

`plotmatrix`: Scatter plot matrix

####  Polar Plots

`polarplot`: Plot line in polar coordinates

`polarscatter`: Scatter chart in polar coordinates

`polarhistogram`: Histogram chart in polar coordinates

`compass`: Plot arrows emanating from origin

`ezpolar`: Easy-to-use polar coordinate plotter

`rlim`: Set or query r-axis limits for polar axes

`thetalim`: Set or query theta-axis limits for polar axes

`rticks`: Set or query r-axis tick values

`thetaticks`: Set or query theta-axis tick values

`rticklabels`: Set or query r-axis tick labels

`thetaticklabels`: Set or query theta-axis tick labels

`rtickformat`: Specify r-axis tick label format

`thetatickformat`: Specify theta-axis tick label format

`rtickangle`: Rotate r-axis tick labels

`polaraxes`: Create polar axes

####  Contour Plots

`contour`: Contour plot of matrix

`contourf`: Filled 2-D contour plot

`contourc`: Low-level contour plot computation

`contour3`: 3-D contour plot

`contourslice`: Draw contours in volume slice planes

`clabel`: Label contour plot elevation

`fcontour`: Plot contours

####  Vector Fields

`feather`: Plot velocity vectors

`quiver`: Quiver or velocity plot

`compass`: Plot arrows emanating from origin

`quiver3`: 3-D quiver or velocity plot

`streamslice`: Plot streamlines in slice planes

`streamline`: Plot streamlines from 2-D or 3-D vector data

####  Surfaces, Volumes, and Polygons
##### Surface and Mesh Plots

`surf`: 3-D shaded surface plot

`surfc`: Contour plot under a 3-D shaded surface plot 

`surface`: Create surface object

`surfl`: Surface plot with colormap-based lighting

`surfnorm`: Compute and display 3-D surface normals

`mesh`: Mesh plot

`meshc`: Plot a contour graph under mesh graph

`meshz`: Plot a curtain around mesh plot

`hidden`: Remove hidden lines from mesh plot

`fsurf`: Plot 3-D surface

`fmesh`: Plot 3-D mesh

`fimplicit3`: Plot 3-D implicit function

`waterfall`: Waterfall plot

`ribbon`: Ribbon plot

`contour3`: 3-D contour plot

`peaks`: Example function of two variables

`cylinder`: Generate cylinder

`ellipsoid`: Generate ellipsoid

`sphere`: Generate sphere

`pcolor`: Pseudocolor (checkerboard) plot

`surf2patch`: Convert surface data to patch data

##### Volume Visualization

`contourslice`: Draw contours in volume slice planes

`flow`: Simple function of three variables

`isocaps`: Compute isosurface end-cap geometry

`isocolors`: Calculate isosurface and patch colors

`isonormals`: Compute normals of isosurface vertices

`isosurface`: Extract isosurface data from volume data

`reducepatch`: Reduce number of patch faces

`reducevolume`: Reduce number of elements in volume data set

`shrinkfaces`: Reduce  size of patch faces

`slice`: Volumetric slice plot

`smooth3`: Smooth 3-D data

`subvolume`: Extract subset of volume data set

`volumebounds`: Coordinate and color limits for volume data

`coneplot`: Plot velocity vectors as cones in 3-D vector field

`curl`: Compute curl and angular velocity of vector field

`divergence`: Compute divergence of vector field

`interpstreamspeed`: Interpolate stream-line vertices from flow speed

`stream2`: Compute 2-D streamline data

`stream3`: Compute 3-D streamline data

`streamline`: Plot streamlines from 2-D or 3-D vector data

`streamparticles`: Plot stream particles

`streamribbon`: 3-D stream ribbon plot from vector volume data

`streamslice`: Plot streamlines in slice planes

`streamtube`: Create 3-D stream tube plot

##### Polygons

`fill`: Filled 2-D polygons

`fill3`: Filled 3-D polygons

`patch`: Create one or more filled polygons

`surf2patch`: Convert surface data to patch data

####  Animation

`movie`: Play recorded movie frames

`getframe`: Capture axes or figure as movie frame

`frame2im`: Return image data associated with movie frame

`im2frame`: Convert image to movie frame

`animatedline`: Create animated line

`comet`: 2-D comet plot

`comet3`: 3-D comet plot

`drawnow`: Update figures and process callbacks

`refreshdata`: Refresh data in graph when data source is specified

`Animated Line`: Line animations

### Formatting and Annotation
####  Titles and Labels

`title`: Add title to axes or legend

`xlabel`: Label  x-axis

`ylabel`: Label  y-axis

`zlabel`: Label  z-axis

`clabel`: Label contour plot elevation

`legend`: Add legend to axes

`colorbar`: Colorbar showing color scale

`text`: Add text descriptions to data points

`texlabel`: Format text with TeX characters

`gtext`: Add text to figure using mouse

`line`: Create line object

`rectangle`: Create rectangle with sharp or curved corners

`annotation`: Create annotations

####  Axes Appearance

`xlim`: Set or query x-axis limits

`ylim`: Set or query y-axis limits

`zlim`: Set or query z-axis limits

`axis`: Set axis limits and aspect ratios

`box`: Display axes outline

`daspect`: Control data unit length along each axis

`pbaspect`: Control relative lengths of each axis

`grid`: Display or hide axes grid lines

`xticks`: Set or query x-axis tick values

`yticks`: Set or query y-axis tick values

`zticks`: Set or query z-axis tick values

`xticklabels`: Set or query x-axis tick labels

`yticklabels`: Set or query y-axis tick labels

`zticklabels`: Set or query z-axis tick labels

`xtickformat`: Specify x-axis tick label format

`ytickformat`: Specify y-axis tick label format

`ztickformat`: Specify z-axis tick label format

`xtickangle`: Rotate x-axis tick labels

`ytickangle`: Rotate y-axis tick labels

`ztickangle`: Rotate z-axis tick labels

`datetick`: Date formatted tick labels

`ruler2num`: Convert data from specific ruler to numeric data

`num2ruler`: Convert numeric data to use with specific ruler

`hold`: Retain current plot when adding new plots

`subplot`: Create axes in tiled positions

`yyaxis`: Create chart with two y-axes

`cla`: Clear axes

`axes`: Create axes graphics object

`figure`: Create figure window

####  Colormaps

`colormap`: View and set current colormap

`colormapeditor`: Open colormap editor

`colorbar`: Colorbar showing color scale

`brighten`: Brighten or darken colormap

`contrast`: Grayscale colormap for contrast enhancement

`shading`: Set color shading properties

`graymon`: Set default figure properties for grayscale monitors

`caxis`: Color axis scaling

`hsv2rgb`: Convert HSV colormap to RGB colormap

`rgb2hsv`: Convert RGB colormap to HSV colormap

`rgbplot`: Plot colormap

`spinmap`: Spin colormap

`colordef`: Set default property values to display different color schemes

`whitebg`: Change axes background color

####  3-D Scene Control
##### Camera Views

`view`: Viewpoint specification

`makehgtform`: Create 4-by-4 transform matrix

`viewmtx`: View transformation matrices

`cameratoolbar`: Control camera toolbar programmatically

`campan`: Rotate camera target around camera position

`camzoom`: Zoom in and out on scene

`camdolly`: Move camera position and target

`camlookat`: Position camera to view object or group of objects

`camorbit`: Rotate camera position around camera target

`campos`: Set or query camera position

`camproj`: Set or query projection type

`camroll`: Rotate camera about view axis

`camtarget`: Set or query location of camera target

`camup`: Set or query camera up vector

`camva`: Set or query camera view angle

##### Lighting and Transparency

`camlight`: Create or move light object in camera coordinates

`light`: Create light object

`lightangle`: Create or position light object in spherical coordinates

`lighting`: Specify lighting algorithm

`diffuse`: Calculate diffuse reflectance

`material`: Control reflectance properties of surfaces and patches

`specular`: Calculate specular reflectance

`alim`: Set or query axes alpha limits

`alpha`: Add transparency to objects in axes

`alphamap`: Specify figure alphamap (transparency)

### Images

`imshow`: Display image

`image`: Display image from array

`imagesc`: Display image with scaled colors

`imread`: Read image from graphics file

`imwrite`: Write image to graphics file

`imfinfo`: Information about graphics file

`imformats`: Manage image file format registry

`frame2im`: Return image data associated with movie frame

`im2frame`: Convert image to movie frame

`im2java`: Convert image to Java image

`im2double`: Convert image to double precision

`ind2rgb`: Convert indexed image to RGB image

`rgb2gray`: Convert RGB image or colormap to grayscale

`rgb2ind`: Convert RGB image to indexed image

`imapprox`: Approximate indexed image by reducing number of colors

`dither`: Convert image, increasing apparent color resolution by dithering

`cmpermute`: Rearrange colors in colormap

`cmunique`: Eliminate duplicate colors in colormap; convert grayscale or truecolor image to indexed image

### Printing and Saving

`print`: Print figure or save to specific file format

`saveas`: Save figure to specific file format

`getframe`: Capture axes or figure as movie frame

`savefig`: Save figure and contents to FIG-file

`openfig`: Open figure saved in FIG-file

`orient`: Hardcopy paper orientation

`hgexport`: Export figure

`printopt`: Configure printer defaults

### Graphics Objects
####  Graphics Object Properties

`get`: Query graphics object properties

`set`: Set graphics object properties

`reset`: Reset graphics object properties to their defaults

`inspect`: Open Property Inspector

####  Graphics Object Identification

`gca`: Current axes handle

`gcf`: Current figure handle

`gcbf`: Handle of figure containing object whose callback is executing

`gcbo`: Handle of object whose callback is executing

`gco`: Handle of current object

`groot`: Graphics root object

`ancestor`: Ancestor of graphics object

`allchild`: Find all children of specified objects

`findall`: Find all graphics objects

`findobj`: Locate graphics objects with specific properties

`findfigs`: Find visible offscreen figures

`gobjects`: Initialize array for graphics objects

`isgraphics`: True for valid graphics object handles

`ishandle`: Test for valid graphics or Java object handle

`copyobj`: Copy graphics objects and their descendants

`delete`: Delete files or objects

####  Graphics Object Programming

`gobjects`: Initialize array for graphics objects

`isgraphics`: True for valid graphics object handles

`isempty`: Determine whether array is empty

`isequal`: Determine array equality

`isa`: Determine if input is object of specified class

`clf`: Clear current figure window

`cla`: Clear axes

`close`: Remove specified figure

####  Interactive Control and Callbacks

`uicontextmenu`: Create context menu

`uimenu`: Create menus and menu items on figure windows

`dragrect`: Drag rectangles with mouse

`rbbox`: Create rubberband box for area selection

`refresh`: Redraw current figure

`shg`: Show most recent graph window

####  Object Containers

`hggroup`: Create group object

`hgtransform`: Create transform graphics object

`makehgtform`: Create 4-by-4 transform matrix

`eye`: Identity matrix

####  Specifying Target for Graphics Output

`hold`: Retain current plot when adding new plots

`ishold`: Current hold state

`newplot`: Determine where to draw graphics objects

`clf`: Clear current figure window

`cla`: Clear axes

### Graphics Performance

`drawnow`: Update figures and process callbacks

`opengl`: Control OpenGL rendering

## Data Import and Analysis

### Data Import and Export

####  Standard File Formats

##### Text Files

`readtable`: Create table from file

`detectImportOptions`: Create import options based on file content

`writetable`: Write table to file

`textscan`: Read formatted data from text file or string

`dlmread`: Read ASCII-delimited file of numeric data into matrix

`dlmwrite`: Write matrix to ASCII-delimited file

`csvread`: Read comma-separated value (CSV) file

`csvwrite`: Write comma-separated value file

`type`: Display contents of file

`DelimitedTextImportOptions`: Import options object for delimited text

##### Spreadsheets

`readtable`: Create table from file

`detectImportOptions`: Create import options based on file content

`writetable`: Write table to file

`xlsfinfo`: Determine if file contains Microsoft Excel spreadsheet

`xlsread`: Read Microsoft Excel spreadsheet file

`xlswrite`: Write Microsoft Excel spreadsheet file

`importdata`: Load data from file

`SpreadsheetImportOptions`: Import options object for Spreadsheets

##### Images

`im2java`: Convert image to Java image

`imfinfo`: Information about graphics file

`imread`: Read image from graphics file

`imwrite`: Write image to graphics file

`Tiff`: MATLAB Gateway to LibTIFF library routines

##### Scientific Data

###### NetCDF Files

`nccreate`: Create variable in NetCDF file

`ncdisp`: Display contents of NetCDF data source in Command Window

`ncinfo`:  Return information about NetCDF data source

`ncread`: Read data from variable in NetCDF data source

`ncreadatt`:  Read attribute value from NetCDF data source

`ncwrite`:  Write data to NetCDF file

`ncwriteatt`: Write attribute to NetCDF file

`ncwriteschema`: Add NetCDF schema definitions to NetCDF file

###### HDF5 Files

###### High-Level Functions

`h5create`: Create HDF5 data set

`h5disp`: Display contents of HDF5 file

`h5info`: Return information about HDF5 file

`h5read`: Read data from HDF5 data set

`h5readatt`: Read attribute from HDF5 file

`h5write`: Write to HDF5 data set

`h5writeatt`: Write HDF5 attribute

###### Low-Level Functions

###### Library (H5)

`H5.close`: Close HDF5 library

`H5.garbage_collect`: Free unused memory in HDF5 library

`H5.get_libversion`: Version of HDF5 library

`H5.open`: Open HDF5 library

`H5.set_free_list_limits`: Set size limits on free lists

###### Attribute (H5A)

`H5A.close`: Close specified attribute

`H5A.create`: Create attribute

`H5A.delete`: Delete attribute

`H5A.get_info`: Information about attribute

`H5A.get_name`: Attribute name

`H5A.get_space`: Copy of attribute data space

`H5A.get_type`: Copy of attribute data type

`H5A.iterate`: Execute function for attributes attached to object

`H5A.open`: Open attribute

`H5A.open_by_idx`: Open attribute specified by index

`H5A.open_by_name`: Open attribute specified by name

`H5A.read`: Read attribute

`H5A.write`: Write attribute

###### Dataset (H5D)

`H5D.close`: Close dataset

`H5D.create`: Create new dataset

`H5D.get_access_plist`: Copy of dataset access property list

`H5D.get_create_plist`: Copy of dataset creation property list

`H5D.get_offset`: Location of dataset in file

`H5D.get_space`: Copy of dataset data space

`H5D.get_space_status`: Determine if space is allocated

`H5D.get_storage_size`: Determine required storage size

`H5D.get_type`: Copy of datatype

`H5D.open`: Open specified dataset

`H5D.read`: Read data from HDF5 dataset

`H5D.set_extent`: Change size of dataset dimensions

`H5D.vlen_get_buf_size`: Determine variable length storage requirements

`H5D.write`: Write data to HDF5 dataset

###### Dimension Scale (H5DS)

`H5DS.attach_scale`: Attach dimension scale to specific dataset dimension

`H5DS.detach_scale`: Detach dimension scale from specific dataset dimension

`H5DS.get_label`: Retrieve label from specific dataset dimension

`H5DS.get_num_scales`: Number of scales attached to dataset dimension

`H5DS.get_scale_name`: Name of dimension scale

`H5DS.is_scale`: Determine if dataset is a dimension scale

`H5DS.iterate_scales`: Iterate on scales attached to dataset dimension

`H5DS.set_label`: Set label for dataset dimension

`H5DS.set_scale`: Convert dataset to dimension scale

###### Error (H5E)

`H5E.clear`: Clear error stack

`H5E.get_major`: Description of major error number

`H5E.get_minor`: Description of minor error number

`H5E.walk`: Walk error stack

###### File (H5F)

`H5F.close`: Close HDF5 file

`H5F.create`: Create HDF5 file

`H5F.flush`: Flush buffers to disk

`H5F.get_access_plist`: File access property list

`H5F.get_create_plist`: File creation property list

`H5F.get_filesize`: Size of HDF5 file

`H5F.get_freespace`: Amount of free space in file

`H5F.get_info`: Global information about file

`H5F.get_mdc_config`: Metadata cache configuration

`H5F.get_mdc_hit_rate`: Metadata cache hit-rate

`H5F.get_mdc_size`: Metadata cache size data

`H5F.get_name`: Name of HDF5 file

`H5F.get_obj_count`: Number of open objects in HDF5 file

`H5F.get_obj_ids`: List of open HDF5 file objects

`H5F.is_hdf5`: Determine if file is HDF5

`H5F.mount`: Mount HDF5 file onto specified location

`H5F.open`: Open HDF5 file

`H5F.reopen`: Reopen HDF5 file

`H5F.set_mdc_config`: Configure HDF5 file metadata cache

`H5F.unmount`: Unmount file or group from mount point

###### Group (H5G)

`H5G.close`: Close group

`H5G.create`: Create group

`H5G.get_info`: Information about group

`H5G.open`: Open specified group

###### Identifier (H5I)

`H5I.dec_ref`: Decrement reference count

`H5I.get_file_id`: File identifier for specified object

`H5I.get_name`: Name of object

`H5I.get_ref`: Reference count of object

`H5I.get_type`: Type of object

`H5I.inc_ref`: Increment reference count of specified object

`H5I.is_valid`: Determine if specified identifier is valid

###### Link (H5L)

`H5L.copy`: Copy link from source location to destination location

`H5L.create_external`: Create soft link to external object

`H5L.create_hard`: Create hard link

`H5L.create_soft`: Create soft link

`H5L.delete`: Remove link

`H5L.exists`: Determine if link exists

`H5L.get_info`: Information about link

`H5L.get_name_by_idx`: Information about link specified by index

`H5L.get_val`: Value of symbolic link

`H5L.iterate`: Iterate over links

`H5L.iterate_by_name`: Iterate through links in group specified by name

`H5L.move`: Rename link

`H5L.visit`: Recursively iterate through links in group specified by group identifier

`H5L.visit_by_name`: Recursively iterate through links in group specified by location and group name

###### MATLAB (H5ML)

`H5ML.compare_values`: Numerically compare two HDF5 values

`H5ML.get_constant_names`: Constants known by HDF5 library

`H5ML.get_constant_value`: Value corresponding to a string

`H5ML.get_function_names`: Functions provided by HDF5 library

`H5ML.get_mem_datatype`: Data type for dataset ID

###### Object (H5O)

`H5O.close`: Close object

`H5O.copy`: Copy object from source location to destination location

`H5O.get_comment`: Get comment for object specified by object identifier

`H5O.get_comment_by_name`: Get comment for object specified by location and object name

`H5O.get_info`: Object metadata

`H5O.link`: Create hard link to specified object

`H5O.open`: Open specified object

`H5O.open_by_idx`: Open object specified by index

`H5O.set_comment`: Set comment for object specified by object identifier

`H5O.set_comment_by_name`: Set comment for object specified by location and object name

`H5O.visit`: Visit objects specified by object identifier

`H5O.visit_by_name`: Visit objects specified by location and object name

###### Property (H5P)
###### General Property List Operations

`H5P.close`: Close property list

`H5P.copy`: Copy of property list

`H5P.create`: Create new property list

`H5P.get_class`: Property list class

###### Generic Property List Operations

`H5P.close_class`: Close property list class

`H5P.equal`: Determine equality of property lists

`H5P.exist`: Determine if specified property exists in property list

`H5P.get`: Value of specified property in property list

`H5P.get_class_name`: Name of property list class

`H5P.get_class_parent`: Identifier for parent class

`H5P.get_nprops`: Query number of properties in property list or class

`H5P.get_size`: Query size of property value in bytes

`H5P.isa_class`: Determine if property list is member of class

`H5P.iterate`: Iterate over properties in property list

`H5P.set`: Set property list value

###### Dataset Access, Memory, and Transfer Properties

`H5P.get_btree_ratios`: B-tree split ratios

`H5P.get_chunk_cache`: Raw data chunk cache parameters

`H5P.get_edc_check`: Determine if error detection is enabled

`H5P.get_hyper_vector_size`: Number of I/O vectors

`H5P.set_btree_ratios`: Set B-tree split ratios for dataset transfer

`H5P.set_chunk_cache`: Set raw data chunk cache parameters

`H5P.set_edc_check`: Enable error detection for dataset transfer

`H5P.set_hyper_vector_size`: Set number of I/O vectors for hyperslab I/O

###### Dataset Creation Properties

`H5P.all_filters_avail`: Determine availability of all filters

`H5P.fill_value_defined`: Determine if fill value is defined

`H5P.get_alloc_time`: Return timing of storage space allocation

`H5P.get_chunk`: Return size of chunks

`H5P.get_external`: Return information about external file

`H5P.get_external_count`: Return count of external files

`H5P.get_fill_time`: Return time when fill values are written to dataset

`H5P.get_fill_value`: Return dataset fill value

`H5P.get_filter`: Return information about filter in pipeline

`H5P.get_filter_by_id`: Return information about specified filter

`H5P.get_layout`: Determine layout of raw data for dataset

`H5P.get_nfilters`: Return number of filters in pipeline

`H5P.modify_filter`: Modify filter in pipeline

`H5P.remove_filter`: Remove filter from property list

`H5P.set_alloc_time`: Set timing for storage space allocation

`H5P.set_chunk`: Set chunk size

`H5P.set_deflate`: Set compression method and compression level

`H5P.set_external`: Add additional file to external file list

`H5P.set_fill_time`: Set time when fill values are written to dataset

`H5P.set_fill_value`: Set fill value for dataset creation property list

`H5P.set_filter`: Add filter to filter pipeline

`H5P.set_fletcher32`: Set Fletcher32 checksum filter in dataset creation

`H5P.set_layout`: Set type of storage for dataset

`H5P.set_nbit`: Set N-Bit filter

`H5P.set_scaleoffset`: Set Scale-Offset filter

`H5P.set_shuffle`: Set shuffle filter

###### File Access Properties

`H5P.get_alignment`: Retrieve alignment properties

`H5P.get_driver`: Low-level file driver

`H5P.get_family_offset`: Offset for family file driver

`H5P.get_fapl_core`: Information about core file driver properties

`H5P.get_fapl_family`: File access property list information

`H5P.get_fapl_multi`: Information about multifile access property list

`H5P.get_fclose_degree`: File close degree

`H5P.get_libver_bounds`: Library version bounds settings

`H5P.get_gc_references`: Garbage collection references setting

`H5P.get_mdc_config`: Metadata cache configuration

`H5P.get_meta_block_size`: Metadata block size setting

`H5P.get_multi_type`: Type of data property for MULTI driver

`H5P.get_sieve_buf_size`: Maximum data sieve buffer size

`H5P.get_small_data_block_size`: Small data block size setting

`H5P.set_alignment`: Set alignment properties for file access property list

`H5P.set_family_offset`: Set offset property for family of files

`H5P.set_fapl_core`: Modify file access to use H5FD_CORE driver

`H5P.set_fapl_family`: Set file access to use family driver

`H5P.set_fapl_log`: Set use of logging driver

`H5P.set_fapl_multi`: Set use of multifile driver

`H5P.set_fapl_sec2`: Set file access for sec2 driver

`H5P.set_fapl_split`: Set file access for emulation of split file driver

`H5P.set_fapl_stdio`: Set file access for standard I/O driver

`H5P.set_fclose_degree`: Set file access for file close degree

`H5P.set_gc_references`: Set garbage collection references flag

`H5P.set_libver_bounds`: Set library version bounds for objects

`H5P.set_mdc_config`: Set initial metadata cache configuration

`H5P.set_meta_block_size`: Set minimum metadata block size

`H5P.set_multi_type`: Specify type of data accessed with MULTI driver

`H5P.set_sieve_buf_size`: Set maximum size of data sieve buffer

`H5P.set_small_data_block_size`: Set size of block reserved for small data

###### File Creation Properties

`H5P.get_istore_k`: Return 1/2 rank of indexed storage B-tree

`H5P.get_sizes`: Return size of offsets and lengths

`H5P.get_sym_k`: Return size of B-tree 1/2 rank and leaf node 1/2 size

`H5P.get_userblock`: Return size of user block

`H5P.get_version`: Return version information for file creation property list

`H5P.set_istore_k`: Set size of parameter for indexing chunked datasets

`H5P.set_sizes`: Set byte size of offsets and lengths

`H5P.set_sym_k`: Set size of parameters used to control symbol table nodes

`H5P.set_userblock`: Set user block size

###### Object Copy and Object Creation Properties

`H5P.get_attr_creation_order`: Return tracking order and indexing settings

`H5P.get_attr_phase_change`: Retrieve attribute phase change thresholds

`H5P.get_copy_object`: Return properties to be used when object is copied

`H5P.set_attr_creation_order`: Set tracking of attribute creation order

`H5P.set_attr_phase_change`: Set attribute storage phase change thresholds

`H5P.set_copy_object`: Set properties to be used when objects are copied

###### Group Creation Properties

`H5P.get_create_intermediate_group`: Determine creation of intermediate groups

`H5P.get_link_creation_order`: Query if link creation order is tracked

`H5P.get_link_phase_change`: Query settings for conversion between groups

`H5P.set_create_intermediate_group`: Set creation of intermediate groups

`H5P.set_link_creation_order`: Set creation order tracking and indexing

`H5P.set_link_phase_change`: Set parameters for group conversion

###### HDF5 String Properties

`H5P.get_char_encoding`: Return character encoding

`H5P.set_char_encoding`: Set character encoding used to encode strings

###### Reference (H5R)

`H5R.create`: Create reference

`H5R.dereference`: Open object specified by reference

`H5R.get_name`: Name of referenced object

`H5R.get_obj_type`: Type of referenced object

`H5R.get_region`: Copy of data space of specified region

###### Dataspace (H5S)

`H5S.copy`: Create copy of data space

`H5S.create`: Create new data space

`H5S.close`: Close data space

`H5S.create_simple`: Create new simple data space

`H5S.extent_copy`: Copy extent from source to destination data space

`H5S.is_simple`: Determine if data space is simple

`H5S.offset_simple`: Set offset of simple data space

`H5S.select_all`: Select entire extent of data space

`H5S.select_elements`: Specify coordinates to include in selection

`H5S.select_hyperslab`: Select hyperslab region

`H5S.select_none`: Reset selection region to include no elements

`H5S.select_valid`: Determine validity of selection

`H5S.set_extent_none`: Remove extent from data space

`H5S.set_extent_simple`: Set size of data space

`H5S.get_select_bounds`: Bounding box of data space selection

`H5S.get_select_elem_npoints`: Number of element points in selection

`H5S.get_select_elem_pointlist`: Element points in data space selection

`H5S.get_select_hyper_blocklist`: List of hyperslab blocks

`H5S.get_select_hyper_nblocks`: Number of hyperslab blocks

`H5S.get_select_npoints`: Number of elements in data space selection

`H5S.get_select_type`: Type of data space selection

`H5S.get_simple_extent_dims`: Data space size and maximum size

`H5S.get_simple_extent_ndims`: Data space rank

`H5S.get_simple_extent_npoints`: Number of elements in data space

`H5S.get_simple_extent_type`: Data space class

###### Datatype (H5T)
###### General Data Type Operation

`H5T.close`: Close data type

`H5T.commit`: Commit transient data type

`H5T.committed`: Determine if data type is committed

`H5T.copy`: Copy data type

`H5T.create`: Create new data type

`H5T.detect_class`: Determine of data type contains specific class

`H5T.equal`: Determine equality of data types

`H5T.get_class`: Data type class identifier

`H5T.get_create_plist`: Copy of data type creation property list

`H5T.get_native_type`: Native data type of dataset data type

`H5T.get_size`: Size of data type in bytes

`H5T.get_super`: Base data type

`H5T.lock`: Lock data type

`H5T.open`: Open named data type

###### Array Data Type

`H5T.array_create`: Create array data type object

`H5T.get_array_dims`: Array dimension extents

`H5T.get_array_ndims`: Rank of array data type

###### Atomic Data Type Properties

`H5T.get_cset`: Character set of string data type

`H5T.get_ebias`: Exponent bias of floating-point type

`H5T.get_fields`: Floating-point data type bit field information

`H5T.get_inpad`: Internal padding type for floating-point data types

`H5T.get_norm`: Mantissa normalization type

`H5T.get_offset`: Bit offset of first significant bit

`H5T.get_order`: Byte order of atomic data type

`H5T.get_pad`: Padding type of least and most-significant bits

`H5T.get_precision`: Precision of atomic data type

`H5T.get_sign`: Sign type for integer data type

`H5T.get_strpad`: Storage mechanism for string data type

`H5T.set_cset`: Set character dataset for string data type

`H5T.set_ebias`: Set exponent bias of floating-point data type

`H5T.set_fields`: Set sizes and locations of floating-point bit fields

`H5T.set_inpad`: Specify how unused internal bits are to be filled

`H5T.set_norm`: Set mantissa normalization of floating-point data type

`H5T.set_offset`: Set bit offset of first significant bit

`H5T.set_order`: Set byte ordering of atomic data type

`H5T.set_pad`: Set padding type for least and most significant bits

`H5T.set_precision`: Set precision of atomic data type

`H5T.set_sign`: Set sign property for integer data type

`H5T.set_size`: Set size of data type in bytes

`H5T.set_strpad`: Set storage mechanism for string data type

###### Compound Data Type

`H5T.get_member_class`: Data type class for compound data type member

`H5T.get_member_index`: Index of compound or enumeration type member

`H5T.get_member_name`: Name of compound or enumeration type member

`H5T.get_member_offset`: Offset of field of compound data type

`H5T.get_member_type`: Data type of specified member

`H5T.get_nmembers`: Number of elements in enumeration type

`H5T.insert`: Add member to compound data type

`H5T.pack`: Recursively remove padding from compound data type

###### Enumeration Data Type

`H5T.enum_create`: Create new enumeration data type

`H5T.enum_insert`: Insert enumeration data type member

`H5T.enum_nameof`: Name of enumeration data type member

`H5T.enum_valueof`: Value of enumeration data type member

`H5T.get_member_value`: Value of enumeration data type member

###### Opaque Data Type Properties

`H5T.get_tag`: Tag associated with opaque data type

`H5T.set_tag`: Tag opaque data type with description

###### Variable-length Data Type

`H5T.is_variable_str`: Determine if data type is variable-length string

`H5T.vlen_create`: Create new variable-length data type

###### Filters and Compression (H5Z)

`H5Z.filter_avail`: Determine if filter is available

`H5Z.get_filter_info`: Information about filter

###### HDF4 Files
###### High-Level Functions

`hdfinfo`: Information about HDF4 or HDF-EOS file

`hdfread`: Read data from HDF4 or HDF-EOS file

`hdftool`: Browse and import data from HDF4 or HDF-EOS files

`imread`: Read image from graphics file

`imwrite`: Write image to graphics file

###### Low-Level Functions

`hdfan`: Gateway to HDF multifile annotation (AN) interface

`hdfhx`: Gateway to HDF external data (HX) interface

`hdfh`: Gateway to HDF H interface

`hdfhd`: Gateway to HDF HD interface

`hdfhe`: Gateway to HDF HE interface

`hdfml`: Utilities for working with MATLAB HDF gateway functions

`hdfpt`: Interface to HDF-EOS Point object

`hdfv`: Gateway to HDF Vgroup (V) interface

`hdfvf`: Gateway to VF functions in HDF Vdata interface

`hdfvh`: Gateway to VH functions in HDF Vdata interface

`hdfvs`: Gateway to VS functions in HDF Vdata interface

`hdfdf24`: Gateway to HDF 24-bit raster image (DF24) interface

`hdfdfr8`: Gateway to HDF 8-bit raster image (DFR8) interface

###### FITS Files
###### High-Level Functions

`fitsdisp`: Display FITS metadata

`fitsinfo`: Information about FITS file

`fitsread`: Read data from FITS file

`fitswrite`: Write image to FITS file

###### Low-Level Functions
###### File Access

`createFile`: Create FITS file

`openFile`: Open FITS file

`closeFile`: Close FITS file

`deleteFile`: Delete FITS file

`fileName`: Name of FITS file

`fileMode`: I/O mode of FITS file

###### Image Manipulation

`createImg`: Create FITS image

`getImgSize`: Size of image

`getImgType`: Data type of image

`insertImg`: Insert FITS image after current image

`readImg`: Read image data

`setBscale`: Reset image scaling

`writeImg`: Write to FITS image

###### Keywords

`readCard`: Header record of keyword

`readKey`: Keyword

`readKeyCmplx`: Keyword as complex scalar value

`readKeyDbl`: Keyword as double precision value

`readKeyLongLong`: Keyword as int64

`readKeyLongStr`: Long string value

`readKeyUnit`: Physical units string from keyword

`readRecord`: Header record specified by number

`writeComment`: Write or append COMMENT keyword to CHU

`writeDate`: Write DATE keyword to CHU

`writeKey`: Update or add new keyword into current HDU

`writeKeyUnit`: Write physical units string

`writeHistory`: Write or append HISTORY keyword to CHU

`deleteKey`: Delete key by name

`deleteRecord`: Delete key by record number

`getHdrSpace`: Number of keywords in header

###### Header Data Unit (HDU) Access

`copyHDU`: Copy current HDU from one file to another

`getHDUnum`: Number of current HDU in FITS file

`getHDUtype`: Type of current HDU

`getNumHDUs`: Total number of HDUs in FITS file

`movAbsHDU`: Move to absolute HDU number

`movNamHDU`: Move to first HDU having specific type and keyword values

`movRelHDU`: Move relative number of HDUs from current HDU

`writeChecksum`: Compute and write checksum for current HDU

`deleteHDU`: Delete current HDU in FITS file

###### Image Compression

`imgCompress`: Compress HDU from one file into another

`isCompressedImg`: Determine if current image is compressed

`setCompressionType`: Set image compression type

`setHCompScale`: Set scale parameter for HCOMPRESS algorithm

`setHCompSmooth`: Set smoothing for images compressed with HCOMPRESS

`setTileDim`: Set tile dimensions

###### ASCII and Binary Tables

`createTbl`: Create new ASCII or binary table extension

`insertCol`: Insert column into table

`insertRows`: Insert rows into table

`insertATbl`: Insert ASCII table after current HDU

`insertBTbl`: Insert binary table after current HDU

`deleteCol`: Delete column from table

`deleteRows`: Delete rows from table

`getAColParms`: ASCII table information

`getBColParms`: Binary table information

`getColName`: Table column name

`getColType`: Scaled column data type, repeat value, width

`getEqColType`: Column data type, repeat value, width

`getNumCols`: Number of columns in table

`getNumRows`: Number of rows in table

`readATblHdr`: Read header information from current ASCII table

`readBTblHdr`: Read header information from current binary table

`readCol`: Read rows of ASCII or binary table column

`setTscale`: Reset image scaling

`writeCol`: Write elements into ASCII or binary table column

###### Utilities

`getConstantValue`: Numeric value of named constant

`getVersion`: Revision number of the CFITSIO library

`getOpenFiles`: List of open FITS files

###### Band-Interleaved Files

`multibandread`: Read band-interleaved data from binary file

`multibandwrite`: Write band-interleaved data to file

###### Common Data Format

`cdfinfo`: Information about Common Data Format (CDF) file

`cdfread`: Read data from Common Data Format (CDF) file

`cdfepoch`: Convert date string or serial date number to CDF formatted dates

`todatenum`: Convert CDF epoch object to MATLAB serial date number

##### Audio and Video
###### Reading and Writing Files

`audioinfo`: Information about audio file

`audioread`: Read audio file

`audiowrite`: Write audio file

`VideoReader`: Create object to read video files

`VideoWriter`: Create object to write video files

`mmfileinfo`: Information about multimedia file

`lin2mu`: Convert linear audio signal to mu-law

`mu2lin`: Convert mu-law audio signal to linear

`VideoReader`: Read video files

`VideoWriter`: Write video files

###### Audio Recording and Playback

`audiodevinfo`: Information about audio device

`audioplayer`: Create object for playing audio 

`audiorecorder`: Create object for recording audio

`sound`: Convert matrix of signal data to sound

`soundsc`: Scale data and play as sound

`beep`: Produce operating system beep sound

##### XML Documents

`xmlread`: Read XML document and return Document Object Model node

`xmlwrite`: Write XML Document Object Model node

`xslt`: Transform XML document using XSLT engine

####  Workspace Variables and MAT-Files

`clear`: Remove items from workspace, freeing up system memory

`clearvars`: Clear variables from memory

`disp`: Display value of variable

`openvar`: Open workspace variable in Variables editor or other graphical editing tool

`who`: List variables in workspace

`whos`: List variables in workspace, with sizes and types

`load`: Load variables from file into workspace

`save`: Save workspace variables to file

`matfile`: Access and change variables directly in MAT-files, without loading into memory

####  Low-Level File I/O

`fclose`: Close one or all open files

`feof`: Test for end-of-file

`ferror`: Information about file I/O errors

`fgetl`: Read line from file, removing newline characters

`fgets`: Read line from file, keeping newline characters

`fileread`: Read contents of file as text

`fopen`: Open file, or obtain information about open files

`fprintf`: Write data to text file

`fread`: Read data from binary file

`frewind`: Move file position indicator to beginning of open file

`fscanf`: Read data from text file

`fseek`: Move to specified position in file

`ftell`: Position in open file

`fwrite`: Write data to binary file

####  TCP/IP Communication

`tcpclient`: Create TCP/IP client object to communicate over TCP/IP

`read`: Read data from remote host over TCP/IP

`write`: Write data to remote host over TCP/IP

####  Web Access

`web`: Open Web page or file in browser

`webread`: Read content from RESTful web service

`webwrite`: Write data to RESTful web service

`websave`: Save content from RESTful web service to file

`weboptions`: Specify parameters for RESTful web service

`sendmail`: Send email message to address list

`ftp`: Connect to FTP server

####  JSON Format

`jsondecode`: Decode JSON-formatted text

`jsonencode`: Encode structured MATLAB data as JSON-formatted text

####  Serial Port Devices

`delete (serial)`: Remove serial port object from memory

`fclose (serial)`: Disconnect serial port object from device

`fgetl (serial)`: Read line of ASCII text from device and discard terminator

`fgets (serial)`: Read line of text from device and include terminator

`fopen (serial)`: Connect serial port object to device

`fprintf (serial)`: Write text to device

`fread (serial)`: Read binary data from device

`fscanf (serial)`: Read ASCII data from device, and format as text

`fwrite (serial)`: Write binary data to device

`get (serial)`: Serial port object properties

`instrcallback`: Event information when event occurs

`instrfind`: Read serial port objects from memory to MATLAB workspace

`instrfindall`: Find visible and hidden serial port objects

`isvalid (serial)`: Determine whether serial port objects are valid

`readasync`: Read data asynchronously from device

`record`: Record data and event information to file

`serial`: Create serial port object

`serialbreak`: Send break to device connected to serial port

`set (serial)`: Configure or display serial port object properties

`stopasync`: Stop asynchronous read and write operations

`clear (serial)`: Remove serial port object from MATLAB workspace

`load (serial)`: Load serial port objects and variables into MATLAB workspace

`save (serial)`: Save serial port objects and variables to file

`disp (serial)`: Serial port object summary information

`length (serial)`: Length of serial port object array

`size (serial)`: Size of serial port object array

### Large Files and Big Data
####  Datastore

`tabularTextDatastore`: Create TabularTextDatastore object for collections of tabular text data

`imageDatastore`: Create ImageDatastore object for collections of image data

`spreadsheetDatastore`: Create SpreadsheetDatastore object for collections of spreadsheet data

`fileDatastore`: Create FileDatastore object for collections of custom files

`datastore`: Create datastore for large collections of data

`TabularTextDatastore`: Datastore for tabular text files

`ImageDatastore`: Datastore for image data

`SpreadsheetDatastore`: Datastore for spreadsheet files

`KeyValueDatastore`: Datastore for key-value pair data

`FileDatastore`: Datastore for custom format files

`TallDatastore`: Datastore for checkpointing tall arrays

####  Tall Arrays

`tall`: Create tall array

`datastore`: Create datastore for large collections of data

`mapreducer`: Define execution environment for mapreduce or tall arrays

`gather`: Collect tall array into memory after executing queued operations

`head`: Get top rows of tall array

`tail`: Get bottom rows of tall array

`topkrows`: Top rows in sorted order

`istall`: Determine if input is tall array

`classUnderlying`: Class of underlying data in tall array

`isaUnderlying`: Determine if tall array data is of specified class

`write`: Write tall array to disk for checkpointing

####  MapReduce

`mapreduce`: Programming technique for analyzing data sets that do not fit in memory

`datastore`: Create datastore for large collections of data

`mapreducer`: Define execution environment for mapreduce or tall arrays

`KeyValueStore`: Store key-value pairs for use with mapreduce

`ValueIterator`: An iterator over intermediate values for use with mapreduce

####  Large MAT-Files

`matfile`: Access and change variables directly in MAT-files, without loading into memory

####  Memory Mapping

`memmapfile`: Create memory map to a file

### Preprocessing Data

`ismissing`: Find missing values

`standardizeMissing`: Insert standard missing-value indicators

`rmmissing`: Remove missing entries

`fillmissing`: Fill missing values

`movmean`: Moving mean

`movmedian`: Moving median

`detrend`: Remove linear trends

`filter`: 1-D digital filter

`discretize`: Group data into bins or categories

`histcounts`: Histogram bin counts

`histcounts2`: Bivariate histogram bin counts

`findgroups`: Find groups and return group numbers

`splitapply`: Split data into groups and apply function

`rowfun`: Apply function to table or timetable rows

`varfun`: Apply function to table or timetable variables

`accumarray`: Construct array with accumulation

### Descriptive Statistics

`corrcoef`: Correlation coefficients

`cov`: Covariance

`max`: Largest elements in array

`mean`: Average or mean value of array

`median`: Median value of array

`min`: Smallest elements in array

`mode`: Most frequent values in array

`std`: Standard deviation

`var`: Variance

`cummax`: Cumulative maximum

`cummin`: Cumulative minimum

`movmax`: Moving maximum

`movmean`: Moving mean

`movmedian`: Moving median

`movmin`: Moving minimum

`movstd`: Moving standard deviation

`movsum`: Moving sum

`movvar`: Moving variance

### Visual Exploration

`pan`: Pan view of graph interactively

`zoom`: Turn zooming on or off or magnify by factor

`rotate`: Rotate object about specified origin and direction

`rotate3d`: Rotate 3-D view using mouse

`brush`: Interactively mark, delete, modify, and save observations in graphs

`datacursormode`: Enable, disable, and manage interactive data cursor mode

`ginput`: Graphical input from mouse or cursor

`linkdata`: Automatically update graphs when variables change

`linkaxes`: Synchronize limits of specified 2-D axes

`linkprop`: Keep same value for corresponding properties of graphics objects

`refreshdata`: Refresh data in graph when data source is specified

`figurepalette`: Show or hide Figure Palette

`plotbrowser`: Show or hide figure Plot Browser

`plotedit`: Interactively edit and annotate plots

`plottools`: Show or hide plot tools

`propertyeditor`: Show or hide Property Editor

`propedit`: Open Property Editor

`showplottool`: Show or hide figure plot tool

## Programming Scripts and Functions
### Control Flow

`if, elseif, else`: Execute statements if condition is true

`for`: for loop to repeat specified number of times

`parfor`: Parallel for loop

`switch, case, otherwise`: Execute one of several groups of statements

`try, catch`: Execute statements and catch resulting errors

`while`: while loop to repeat when condition is true

`break`: Terminate execution of for or while loop

`continue`: Pass control to next iteration of for or while loop

`end`: Terminate block of code, or indicate last array index

`pause`: Stop MATLAB execution temporarily

`return`: Return control to invoking function

### Scripts

`edit`: Edit or create file

`input`: Request user input

`publish`: Generate view of MATLAB file in specified format

`notebook`: Open MATLAB Notebook in Microsoft Word software
(on Microsoft Windows platforms)

`grabcode`: Extract MATLAB code from file published to HTML

`snapnow`: Force snapshot of image for inclusion in published document

### Functions
####  Function Basics

`function`: Declare function name, inputs, and outputs

####  Input and Output Arguments

`nargin`: Number of function input arguments

`nargout`: Number of function output arguments

`varargin`: Variable-length input argument list

`varargout`: Variable-length output argument list

`narginchk`: Validate number of input arguments

`nargoutchk`: Validate number of output arguments

`validateattributes`: Check validity of array

`validatestring`: Check validity of text

`inputParser`: Parse function inputs

`inputname`: Variable name of function input

####  Variables

`isvarname`: Determine if input is valid variable name

`matlab.lang.makeUniqueStrings`: Construct unique strings from input strings

`matlab.lang.makeValidName`: Construct valid MATLAB identifiers from input strings

`namelengthmax`: Maximum identifier length

`persistent`: Define persistent variable

`mlock`: Prevent clearing function from memory

`munlock`: Allow clearing functions from memory

`mislocked`: Determine if function is locked in memory

`assignin`: Assign value to variable in specified workspace

`global`: Declare variables as global

####  Error Handling

`try, catch`: Execute statements and catch resulting errors

`error`: Throw error and display message

`warning`: Display warning message

`lastwarn`: Last warning message

`assert`: Throw error if condition false

`onCleanup`: Cleanup tasks upon function completion

### Files and Folders
####  Search Path

`addpath`: Add folders to search path

`rmpath`: Remove folders from search path

`path`: View or change search path

`savepath`: Save current search path

`userpath`: View or change default user work folder

`genpath`: Generate path name

`pathsep`: Search path separator for current platform

`pathtool`: Open Set Path dialog box to view and change search path

`restoredefaultpath`: Restore search path to its factory-installed state

`rehash`: Refresh function and file system path caches

####  File Operations

`dir`: List folder contents

`ls`: List folder contents

`pwd`: Identify current folder

`fileattrib`: Set or get attributes of file or folder

`exist`: Check existence of variable, script, function, folder,
or class

`isdir`: Determine whether input is folder

`type`: Display contents of file

`visdiff`: Compare two text files, MAT-Files, binary files, Zip files, or folders

`what`: List MATLAB files in folder

`which`: Locate functions and files

`cd`: Change current folder

`copyfile`: Copy file or folder

`delete`: Delete files or objects

`recycle`: Set option to move deleted files to recycle folder

`mkdir`: Make new folder

`movefile`: Move file or folder

`rmdir`: Remove folder

`open`: Open file in appropriate application

`winopen`: Open file in appropriate application (Windows)

####  File Compression

`zip`: Compress files into zip file

`unzip`: Extract contents of zip file

`gzip`: Compress files into GNU zip files

`gunzip`: Uncompress GNU zip files

`tar`: Compress files into tar file

`untar`: Extract contents of tar file

####  File Name Construction

`fileparts`: Parts of file name and path

`fullfile`: Build full file name from parts

`filemarker`: Character to separate file name and internal function name

`filesep`: File separator for current platform

`tempdir`: Name of system's temporary folder

`tempname`: Unique name for temporary file

`matlabroot`: Root folder

`toolboxdir`: Root folder for specified toolbox

### Debugging

`dbclear`: Remove breakpoints

`dbcont`: Resume execution

`dbdown`: Reverse dbup workspace shift

`dbquit`: Quit debug mode

`dbstack`: Function call stack

`dbstatus`: List all breakpoints

`dbstep`: Execute next executable line from current breakpoint

`dbstop`: Set breakpoints for debugging

`dbtype`: Display file with line numbers

`dbup`: Shift current workspace to workspace of caller in debug mode

`checkcode`: Check MATLAB code files for possible problems

`keyboard`: Input from keyboard

`mlintrpt`: Run checkcode for file or folder

### Code Editor

`edit`: Edit or create file

### Programming Utilities

`echo`: Display statements during function execution

`eval`: Execute MATLAB expression in text

`evalc`: Evaluate MATLAB expression with capture

`evalin`: Execute MATLAB expression in specified workspace

`feval`: Evaluate function

`run`: Run MATLAB script

`builtin`: Execute built-in function from overloaded method

`matlab.codetools.requiredFilesAndProducts`: List dependencies of MATLAB program files

`mfilename`: File name of currently running code

`pcode`: Create protected function file

`timer`: Create object to schedule execution of MATLAB commands

## App Building
### GUIDE or Programmatic Workflow
####  Components and Layout

`figure`: Create figure window

`axes`: Create axes graphics object

`uicontrol`: Create user interface control object

`uitable`:  Create table user interface component

`uipanel`: Create panel container object

`uibuttongroup`: Create button group to manage radio buttons and toggle buttons

`uitab`: Create tabbed panel

`uitabgroup`: Create container for tabbed panels

`uimenu`: Create menus and menu items on figure windows

`uicontextmenu`: Create context menu

`uitoolbar`: Create toolbar on figure

`uipushtool`: Create push button on toolbar

`uitoggletool`: Create toggle button on toolbar

`actxcontrol`: Create Microsoft ActiveX control in figure window

`align`: Align UI components and graphics objects

`movegui`: Move UI figure to specified location on screen

`getpixelposition`: Get component position in pixels

`setpixelposition`: Set component position in pixels

`listfonts`: List available system fonts

`textwrap`: Wrap text for uicontrol

`uistack`: Reorder visual stacking order of objects

`inspect`: Open Property Inspector

####  Dialog Boxes

`errordlg`: Create error dialog box

`warndlg`: Create warning dialog box

`msgbox`: Create message dialog box

`helpdlg`: Create help dialog box

`waitbar`: Open or update wait bar dialog box

`questdlg`: Create question dialog box

`inputdlg`: Create dialog box that gathers user input

`listdlg`: Create list selection dialog box

`uisetcolor`: Open color picker

`uisetfont`: Open font selection dialog box

`export2wsdlg`: Create dialog box for exporting variables to workspace

`uigetfile`: Open file selection dialog box

`uiputfile`: Open dialog box for saving files

`uigetdir`: Open folder selection dialog box

`uiopen`: Open dialog box for selecting files to load into workspace

`uisave`: Open dialog box for saving variables to MAT-file

`printdlg`: Open figure Print dialog box

`printpreview`: Open figure Print Preview dialog box

`exportsetupdlg`: Open figure Export Setup dialog box

`dialog`: Create empty modal dialog box

`uigetpref`: Conditionally open dialog box according to user preference

####  Coding App Behavior

`guide`: Open GUIDE

`uiwait`: Block program execution and wait to resume

`uiresume`: Resume execution of blocked program

`waitfor`: Block execution and wait for condition

`waitforbuttonpress`: Wait for key press or mouse-button click

`closereq`: Default figure close request function

`getappdata`: Retrieve application-defined data

`setappdata`: Store application-defined data

`isappdata`: True if application-defined data exists

`rmappdata`: Remove application-defined data

`guidata`: Store or retrieve UI data

`guihandles`: Create structure of handles

`uisetpref`: Manage preferences used in uigetpref

### App Designer
####  Components in App Designer

`uiaxes`: Create UI axes for plots in App Designer

`uibutton`: Create push button or state button component

`uibuttongroup`: Create button group to manage radio buttons and toggle buttons

`uicheckbox`: Create check box component

`uidropdown`: Create drop-down component

`uieditfield`: Create text or numeric edit field component

`uilabel`: Create label component

`uilistbox`: Create list box component

`uiradiobutton`: Create radio button component

`uislider`: Create slider component

`uispinner`: Create spinner component

`uitable`:  Create table user interface component

`uitextarea`: Create text area component

`uitogglebutton`: Create toggle button component

`scroll`: Scroll list box item or location into view

`uifigure`: Create UI figure window

`uipanel`: Create panel container object

`uitabgroup`: Create container for tabbed panels

`uitab`: Create tabbed panel

`uigauge`: Create circular, linear, ninety-degree, or semicircular gauge component

`uiknob`: Create continuous or discrete knob component

`uilamp`: Create lamp component

`uiswitch`: Create slider switch, rocker switch, or toggle switch component

`uialert`: Display alert dialog box for UI figure window

`questdlg`: Create question dialog box

`inputdlg`: Create dialog box that gathers user input

`listdlg`: Create list selection dialog box

`uisetcolor`: Open color picker

`uigetfile`: Open file selection dialog box

`uiputfile`: Open dialog box for saving files

`uigetdir`: Open folder selection dialog box

`uiopen`: Open dialog box for selecting files to load into workspace

`uisave`: Open dialog box for saving variables to MAT-file

####  Coding App Behavior in App Designer

`appdesigner`: Create or edit app file in App Designer

### Packaging Apps

`matlab.apputil.create`: Create or modify app project file for packaging app into .mlappinstall file using interactive dialog box

`matlab.apputil.package`: Package app files into .mlappinstall file

`matlab.apputil.install`: Install app from a .mlappinstall file

`matlab.apputil.run`: Run app programmatically

`matlab.apputil.getInstalledAppInfo`: List installed app information

`matlab.apputil.uninstall`: Uninstall app

## Advanced Software Development
### Object-Oriented Programming
####  Class Syntax Guide

`class`: Determine class of object

`isobject`: Determine if input is MATLAB object

`enumeration`: Display class enumeration members and names

`events`: Event names

`methods`: Class method names

`properties`: Class property names

####  Sample Class Implementations

`classdef`: Class definition keywords

####  Class Definition
##### Class Definition and File Organization

`classdef`: Class definition keywords

`import`: Add package or class to current import list

##### Properties

`properties`: Class property names

`isprop`: Determine if property of object

`dynamicprops`: Superclass for classes that support dynamic properties

`meta.DynamicProperty`: Describe dynamic property of MATLAB object

`event.DynamicPropertyEvent`: Event data for dynamic property events

`meta.property`: Describe property of MATLAB class

##### Methods

`methods`: Class method names

`ismethod`: Determine if method of object

`meta.method`: Describe method of MATLAB class

##### Handle Classes

`isequal`: Determine array equality

`eq`: Determine equality

`handle`: Abstract class for deriving handle classes

`matlab.mixin.SetGet`: Derive handle classes with set and get methods

`matlab.mixin.SetGetExactNames`: Require exact name match for set and get methods

`dynamicprops`: Superclass for classes that support dynamic properties

`matlab.mixin.Copyable`: Superclass providing copy functionality for handle objects

##### Events

`events`: Event names

`handle.notify`: Notify listeners that event is occurring

`handle.addlistener`: Create event listener

`event.hasListener`: Determine if listeners exist for event

`event.EventData`: Base class for event data

`event.listener`: Class defining listener objects

`event.PropertyEvent`: Data for property events

`event.proplistener`: Define listener object for property events

##### Class Hierarchies
###### Subclass Definition

`superclasses`: Superclass names

`matlab.mixin.Heterogeneous`: Superclass for heterogeneous array formation

##### Enumerations

`enumeration`: Display class enumeration members and names

`isenum`: Determine if variable is enumeration

`meta.EnumeratedValue`: Describe enumeration member of MATLAB class

####  Class Customization
##### Object Indexing

`numArgumentsFromSubscript`: Number of arguments for customized indexing methods

`subsref`: Redefine subscripted reference for objects

`subsasgn`: Redefine subscripted assignment

`subsindex`: Convert object to array index

`substruct`: Create structure argument for subsasgn or subsref

`builtin`: Execute built-in function from overloaded method

##### Object Arrays

`empty`: Create empty array

`matlab.mixin.Heterogeneous`: Superclass for heterogeneous array formation

##### Object Display

`disp`: Display value of variable

`display`: Display text and numeric expressions

`details`: Display array details

`matlab.mixin.CustomDisplay`: Interface for customizing object display

`matlab.mixin.util.PropertyGroup`: Custom property list for object display

##### Object Save and Load

`saveobj`: Modify save process for object

`loadobj`: Modify load process for object

####  Class Editing

`edit`: Edit or create file

####  Class Metadata

`metaclass`: Obtain meta.class object

`meta.abstractDetails`: Find abstract methods and properties

`meta.class.fromName`: Return meta.class object associated with named class

`meta.package.fromName`: Return meta.package object for specified package

`meta.package.getAllPackages`: Get all top-level packages

`properties`: Class property names

`methods`: Class method names

`events`: Event names

`superclasses`: Superclass names

`meta.class`: Describe MATLAB class

`meta.property`: Describe property of MATLAB class

`meta.method`: Describe method of MATLAB class

`meta.event`: Describe event of MATLAB class

`meta.package`: Describe MATLAB package

`meta.DynamicProperty`: Describe dynamic property of MATLAB object

`meta.EnumeratedValue`: Describe enumeration member of MATLAB class

`meta.MetaData`: Superclass for MATLAB object metadata

### Calling External Functions
####  Call MEX File Functions

`mexext`: Binary MEX file-name extension

`inmem`: Names of functions, MEX-files, classes in memory

####  Call C Shared Libraries

`loadlibrary`: Load C/C++ shared library into MATLAB

`unloadlibrary`: Unload shared library from memory

`libisloaded`: Determine if shared library is loaded

`calllib`: Call function in shared library

`libfunctions`: Return information on functions in shared library

`libfunctionsview`: Display shared library function signatures in window

`libstruct`: Convert MATLAB structure to C-style structure for use with shared library

`libpointer`: Pointer object for use with shared library

`lib.pointer`: Pointer object compatible with C pointer

####  Call Java Libraries

`javaArray`: Construct Java array object

`import`: Add package or class to current import list

`javaclasspath`: Return Java class path or specify dynamic path

`javaaddpath`: Add entries to dynamic Java class path

`javarmpath`: Remove entries from dynamic Java class path

`javachk`: Error message based on Java feature support

`isjava`: Determine if input is Java object

`usejava`: Determine if Java feature is available

`javaMethod`: Call Java method

`javaMethodEDT`: Call Java method from Event Dispatch Thread (EDT)

`javaObject`: Call Java constructor

`javaObjectEDT`: Call Java constructor on Event Dispatch Thread (EDT)

`matlab.exception.JavaException`: Capture error information for Java exception

####  Call .NET Libraries
##### Getting Started with Microsoft .NET

`NET.addAssembly`: Make .NET assembly visible to MATLAB

`NET.isNETSupported`: Check for supported Microsoft .NET Framework

`NET`: Summary of functions in MATLAB .NET interface

`enableNETfromNetworkDrive`: Enable access to .NET commands from network drive

`NET.Assembly`: Members of .NET assembly

`NET.NetException`: Capture error information for .NET exception

##### Data Types

`cell`: Create cell array

`NET.createArray`: Array for nonprimitive .NET types

`NET.disableAutoRelease`: Lock .NET object representing a RunTime Callable Wrapper
(COM Wrapper) so that MATLAB does not release COM object

`NET.enableAutoRelease`: Unlock .NET object representing a RunTime Callable Wrapper
(COM Wrapper) so that MATLAB releases COM object

##### Properties

`NET.setStaticProperty`: Static property or field name

##### Events and Delegates

`BeginInvoke`: Initiate asynchronous .NET delegate call

`EndInvoke`: Retrieve result of asynchronous call initiated by .NET System.Delegate BeginInvoke method

`Combine`: Convenience function for static .NET System.Delegate Combine method

`Remove`: Convenience function for static .NET System.Delegate Remove method

`RemoveAll`: Convenience function for static .NET System.Delegate RemoveAll method

##### Enumerations

`bitand`: Bit-wise AND

`bitor`: Bit-wise OR

`bitxor`: Bit-wise XOR

`bitnot`: .NET enumeration object bit-wise NOT instance method

##### Generic Classes

`NET.convertArray`: Convert numeric MATLAB array to .NET array

`NET.createGeneric`: Create instance of specialized .NET generic type

`NET.invokeGenericMethod`: Invoke generic method of object

`NET.GenericClass`: Represent parameterized generic type definitions

####  Call COM Objects

`actxserver`: Create COM server

`actxcontrol`: Create Microsoft ActiveX control in figure window

`actxcontrollist`: List currently installed Microsoft ActiveX controls

`actxcontrolselect`: Create Microsoft ActiveX control from UI

`actxGetRunningServer`: Handle to running instance of Automation server

`iscom`: Determine whether input is COM or ActiveX object

`isprop`: Determine whether input is COM object property

`get`: Get property value from interface, or display properties

`set`: Set object or interface property to specified value

`addproperty`: Add custom property to COM object

`deleteproperty`: Remove custom property from COM object

`inspect`: Open Property Inspector

`propedit`: Open built-in property page for control

`fieldnames`: Field names of structure, or public fields of COM or Java object

`ismethod`: Determine whether input is COM object method

`methods`: Class method names

`methodsview`: View class methods

`invoke`: Invoke method on COM object or interface, or display methods

`isevent`: Determine whether input is COM object event

`events`: List of events COM object can trigger

`eventlisteners`: List event handler functions associated with COM object events

`registerevent`: Associate event handler for COM object event at run time

`unregisterallevents`: Unregister all event handlers associated with COM object events at run time

`unregisterevent`: Unregister event handler associated with COM object event at run time

`isinterface`: Determine whether input is COM interface

`interfaces`: List custom interfaces exposed by COM server object

`release`: Release COM interface

`delete`: Remove COM control or server

`move`: Move or resize control in parent window

`load`: Initialize control object from file

`save`: Serialize control object to file

####  Call Python Libraries
##### Getting Started with Python

`pyversion`: Change default version of Python interpreter

`pyargs`: Create keyword argument for Python function

`matlab.exception.PyException`: Capture error information for Python exception

##### Data Types

`pyargs`: Create keyword argument for Python function

##### Functions

`pyargs`: Create keyword argument for Python function

### Calling Web Services
####  HTTP Interface

`matlab.net.http.RequestMessage`: HTTP request message

`matlab.net.http.ResponseMessage`: HTTP response message

`matlab.net.http.Message`: HTTP request or response message

`matlab.net.http.MessageType`: HTTP message type

`matlab.net.http.MessageBody`: Body of HTTP message

`matlab.net.http.ProtocolVersion`: HTTP protocol version

`matlab.net.http.RequestLine`: First line of HTTP request message

`matlab.net.http.RequestMethod`: HTTP request method

`matlab.net.http.StartLine`: First line of HTTP message

`matlab.net.http.StatusClass`: Status class of HTTP response

`matlab.net.http.StatusCode`: Status code in HTTP response

`matlab.net.http.StatusLine`: First line of HTTP response message

`matlab.net.http.HeaderField`: Header field of HTTP message

`matlab.net.http.field.AcceptField`: HTTP Accept header field

`matlab.net.http.field.AuthenticateField`: HTTP WWW-Authenticate or Proxy-Authenticate header field

`matlab.net.http.field.AuthenticationInfoField`: HTTP Authentication-Info header field in response message

`matlab.net.http.field.AuthorizationField`: HTTP Authorization or Proxy-Authorization header field

`matlab.net.http.field.ContentLengthField`: HTTP Content-Length field

`matlab.net.http.field.ContentLocationField`: HTTP Content-Location header field

`matlab.net.http.field.ContentTypeField`: HTTP Content-Type header field

`matlab.net.http.field.CookieField`: HTTP Cookie header field

`matlab.net.http.field.DateField`: HTTP Date header field

`matlab.net.http.field.GenericField`: HTTP header field with any name and value

`matlab.net.http.field.HTTPDateField`: HTTP header field containing date

`matlab.net.http.field.IntegerField`: Base class for HTTP header fields containing nonnegative integers

`matlab.net.http.field.LocationField`: HTTP Location header field

`matlab.net.http.field.MediaRangeField`: Base class for HTTP Content-Type and Accept header fields

`matlab.net.http.field.SetCookieField`: HTTP Set-Cookie header field

`matlab.net.http.field.URIReferenceField`: Base class for HTTP header fields containing URI components

`matlab.net.http.AuthenticationScheme`: HTTP Authentication scheme

`matlab.net.http.AuthInfo`: Authentication or authorization information in HTTP messages

`matlab.net.http.Cookie`: HTTP cookie received from server

`matlab.net.http.CookieInfo`: HTTP cookie information

`matlab.net.http.Credentials`: Credentials for authenticating HTTP requests

`matlab.net.http.Disposition`: Results in HTTP log record

`matlab.net.http.HTTPException`: Exception thrown by HTTP services

`matlab.net.http.HTTPOptions`: Options controlling HTTP message exchange

`matlab.net.http.LogRecord`: HTTP history log record

`matlab.net.http.MediaType`: Internet media type used in HTTP headers

`matlab.net.http.ProgressMonitor`: Progress monitor for HTTP message exchange

`matlab.net.URI`: Uniform resource identifier (URI)

`matlab.net.ArrayFormat`: Convert arrays in HTTP queries

`matlab.net.QueryParameter`: Parameter in query portion of uniform resource identifier
(URI)

`matlab.net.base64decode`: Base 64 decoding of string

`matlab.net.base64encode`: Base 64 encoding of byte string or vector

####  WSDL (Web Services Description Language)

`matlab.wsdl.createWSDLClient`: Create interface to SOAP-based web service

`matlab.wsdl.setWSDLToolPath`: Location of WSDL tools

### Toolbox Distribution

`matlab.addons.toolbox.packageToolbox`: Package toolbox project

`matlab.addons.toolbox.toolboxVersion`: Query or modify version of toolbox

`matlab.addons.toolbox.installToolbox`: Install toolbox file

`matlab.addons.toolbox.uninstallToolbox`: Uninstall toolbox

`matlab.addons.toolbox.installedToolboxes`: Return information about installed toolboxes

`builddocsearchdb`: Build searchable documentation database

### Exception Handling

`try, catch`: Execute statements and catch resulting errors

`MException`: Capture error information

`addCause`: Record additional causes of exception

`getReport`: Get error message for exception

`last`: Return last uncaught exception

`rethrow`: Rethrow previously caught exception

`throw`: Throw exception

`throwAsCaller`: Throw exception as if occurs within calling function

### Testing Frameworks
####  Script-Based Unit Tests

`assert`: Throw error if condition false

`runtests`: Run set of tests

`testsuite`: Create suite of tests

`TestResult`: Result of running test suite

####  Function-Based Unit Tests

`functiontests`: Create array of tests from handles to local functions

`runtests`: Run set of tests

`testsuite`: Create suite of tests

`TestSuite.run`: Run TestSuite array using TestRunner object configured for text output

`Test`: Specification of a single test method

`FunctionTestCase`: TestCase used for function-based tests

`TestResult`: Result of running test suite

####  Class-Based Unit Tests

`runtests`: Run set of tests

`testsuite`: Create suite of tests

`matlab.unittest.TestSuite.run`: Run TestSuite array using TestRunner object configured for text output

`matlab.unittest.TestRunner.run`: Run all tests in TestSuite array

`matlab.unittest.TestCase`: Superclass of all matlab.unittest test classes

`matlab.unittest.TestSuite`: Class for grouping tests to run

`matlab.unittest.Test`: Specification of a single test method

`matlab.unittest.TestRunner`: Class for running tests in matlab.unittest framework

`matlab.unittest.TestResult`: Result of running test suite

####  Extend Unit Testing Framework

`matlab.unittest.constraints.Constraint`: Fundamental interface class for comparisons

`matlab.unittest.constraints.BooleanConstraint`: Interface class for boolean combinations of constraints

`matlab.unittest.constraints.Tolerance`: Abstract interface class for tolerances

`matlab.unittest.fixtures.Fixture`: Interface class for test fixtures

`matlab.unittest.diagnostics.Diagnostic`: Fundamental interface class for matlab.unittest diagnostics

`matlab.unittest.diagnostics.ConstraintDiagnostic`: Diagnostics specific to matlab.unittest constraints

`matlab.unittest.plugins.TestRunnerPlugin`: Plugin interface for extending TestRunner

`matlab.unittest.plugins.QualifyingPlugin`: Interface for plugins that perform system-wide qualifications

`matlab.unittest.plugins.OutputStream`: Interface that determines where to send text output

####  Performance Testing Framework

`runperf`: Run set of tests for performance measurement

`testsuite`: Create suite of tests

`matlab.perftest.TimeExperiment`: Interface for measuring execution time of code under test

`matlab.perftest.FixedTimeExperiment`: TimeExperiment that collects fixed number of measurements

`matlab.perftest.FrequentistTimeExperiment`: TimeExperiment that collects variable number of measurements

`matlab.perftest.TestCase`: Superclass of matlab.perftest performance test classes

`matlab.unittest.measurement.MeasurementResult`: Result of measuring test suite

### Performance and Memory

####  Code Performance

`timeit`: Measure time required to run function

`tic`: Start stopwatch timer

`toc`: Read elapsed time from stopwatch

`cputime`: Elapsed CPU time

`profile`: Profile execution time for functions

`bench`: MATLAB benchmark

####  Memory Usage

`memory`: Display memory information

`inmem`: Names of functions, MEX-files, classes in memory

`pack`: Consolidate workspace memory

### System Commands

`clipboard`: Copy and paste text to and from system clipboard

`computer`: Information about computer on which MATLAB software is running

`system`: Execute operating system command and return output

`dos`: Execute DOS command and return output

`unix`: Execute UNIX command and return output

`getenv`: Environment variable

`setenv`: Set environment variable

`perl`: Call Perl script using appropriate operating system executable

`winqueryreg`: Item from Windows registry

`commandhistory`: Open Command History window, or select it if already open

`commandwindow`: Open Command Window, or select it if already open

`filebrowser`: Open Current Folder browser, or select it if already open

`workspace`: Open Workspace browser to manage workspace

`matlab.io.saveVariablesToScript`: Save workspace variables to MATLAB script

`getpref`: Preference

`setpref`: Set preference

`addpref`: Add preference

`rmpref`: Remove preference

`ispref`: Test for existence of preference

### MATLAB API for Other Languages
####  MATLAB Engine API for C, C++, and Fortran

`mex`: Build MEX function from C/C++ or Fortran source code

####  MATLAB Engine API for Java

`matlab.engine.shareEngine`: Convert running MATLAB session to shared session

`matlab.engine.engineName`: Return name of shared MATLAB session

`matlab.engine.isEngineShared`: Determine if MATLAB session is shared

`com.mathworks.engine.MatlabEngine`: Java class using MATLAB as a computational engine

`com.mathworks.matlab.types.Complex`: Java class to pass complex data to and from MATLAB

`com.mathworks.matlab.types.Struct`: Java class to pass MATLAB struct to and from MATLAB

`com.mathworks.matlab.types.CellStr`: Java class to represent MATLAB cell array of char vectors

`com.mathworks.matlab.types.HandleObject`: Java class to represent MATLAB handle objects

####  MATLAB COM Automation Server

`Execute`: Execute MATLAB command in Automation server

`Feval`: Evaluate MATLAB function in Automation server

`GetCharArray`: Character array from Automation server

`PutCharArray`: Store character array in Automation server

`GetFullMatrix`: Matrix from Automation server workspace

`PutFullMatrix`: Matrix in Automation server workspace

`GetVariable`: Data from variable in Automation server workspace

`GetWorkspaceData`: Data from Automation server workspace

`PutWorkspaceData`: Data in Automation server workspace

`MaximizeCommandWindow`: Open Automation server window

`MinimizeCommandWindow`: Minimize size of Automation server window

`Quit`: Terminate MATLAB Automation server

`regmatlabserver`: Register current MATLAB as Automation server

`enableservice`: Enable, disable, or report status of MATLAB Automation server

####  MATLAB Engine API for Python

`matlab.engine.start_matlab`: Start MATLAB Engine for Python

`matlab.engine.find_matlab`: Find shared MATLAB sessions to connect to MATLAB Engine for Python

`matlab.engine.connect_matlab`: Connect shared MATLAB session to MATLAB Engine for Python

`matlab.engine.shareEngine`: Convert running MATLAB session to shared session

`matlab.engine.engineName`: Return name of shared MATLAB session

`matlab.engine.isEngineShared`: Determine if MATLAB session is shared

`matlab.engine.MatlabEngine`: Python object using MATLAB as computational engine within Python session

`matlab.engine.FutureResult`: Results of asynchronous call to MATLAB function stored in Python object

####  MEX File Creation API
##### Executable C/C++ MEX Files

`mex`: Build MEX function from C/C++ or Fortran source code

`dbmex`: Enable MEX-file debugging (on UNIX platforms)

`mex.getCompilerConfigurations`: Get compiler configuration information for building MEX files

##### Call MEX File Functions

`mexext`: Binary MEX file-name extension

`inmem`: Names of functions, MEX-files, classes in memory

##### Share MEX Files

`ver`: Version information for MathWorks products

`computer`: Information about computer on which MATLAB software is running

`mexext`: Binary MEX file-name extension

`mex.getCompilerConfigurations`: Get compiler configuration information for building MEX files

##### Troubleshoot MEX Files

`dbmex`: Enable MEX-file debugging (on UNIX platforms)

`inmem`: Names of functions, MEX-files, classes in memory

`mex`: Build MEX function from C/C++ or Fortran source code

`mexext`: Binary MEX file-name extension

## Desktop Environment
### Startup and Shutdown

`matlab (Windows)`: Start MATLAB program from Windows system prompt

`matlab (Mac)`: Start MATLAB program from Mac Terminal

`matlab (Linux)`: Start MATLAB program from Linux system prompt

`exit`: Terminate MATLAB program (same as quit)

`quit`: Terminate MATLAB program

`matlabrc`: Start up file for MATLAB program

`startup`: Start up file for user-defined options

`finish`: Termination file for MATLAB program

### Basic Settings

`prefdir`: Folder containing preferences, history, and layout files

`preferences`: Open Preferences dialog box

### Platform and License

`version`: Version number for MATLAB and libraries

`ver`: Version information for MathWorks products

`verLessThan`: Compare toolbox version to specified character vector

`license`: Get license number or perform licensing task

`ispc`: Determine if version is for Windows (PC) platform

`ismac`: Determine if version is for Mac OS X platform

`isunix`: Determine if version is for Linux or Mac platforms

`isstudent`: Determine if version is Student Version

`javachk`: Error message based on Java feature support

`usejava`: Determine if Java feature is available

### Help and Support

`doc`: Reference page in Help browser

`help`: Help for functions in Command Window

`docsearch`: Help browser search

`lookfor`: Search for keyword in all help entries

`demo`: Access product examples in Help browser

`echodemo`: Run example script step-by-step in Command Window
