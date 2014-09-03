#getaway

Utility for calculating the best time to book an airline ticket

##Background

According to [CheapAir](http://www.cheapair.com/blog/travel-tips/when-should-you-buy-your-airline-ticket-heres-what-our-data-has-to-say/), the best time to book an airline ticket is 54 days in advance.

##Installation

```bash
make && sudo make install
```

##Usage

```bash
Usage: getaway [-h]|[r] ["date"] [book_time]
```

This will give you the date that is 54 days away from the current date:

```bash
getaway
```

If you want to see 54 days from a specific date:

```bash
getaway "January 1, 1970"
```

If you know your departure date and would like to see what date is 54 days prior:

```bash
getaway -r "December 25, 2014"
```

Don't trust CheapAir's metric of 54 days? Substitue your own:

```bash
getaway "February 14, 2014" 67
```
