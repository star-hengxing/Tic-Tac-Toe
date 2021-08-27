use std::time::Instant;

const WIN:  usize = 3;
const DRAW: usize = 2;
const LOSE: usize = 1;

#[derive(Debug, Clone, Copy, PartialEq)]
enum status_type
{
    O,
    X,
    empty
}

struct game_map
{
    status: [status_type; 9]
}

impl game_map
{
    fn new() -> Self
    {
        game_map { status: [status_type::empty; 9] }
    }

    fn from(arr: [status_type; 9]) -> Self
    {
        game_map { status: arr }
    }

    fn update(&mut self, step: usize, t: status_type) -> &Self
    {
        assert!(step >= 0 && step <= 8);
        self.status[step] = t;
        self
    }

    fn is_full(&self) -> bool
    {
        self.status.iter().all(|&i| i != status_type::empty)
    }

    fn is_win(&self, t: status_type) -> bool
    {
        let cmp = |three : [usize; 3], t : status_type| { three.iter().all(|&i| self.status[i] == t) };
        for i in 0..3
        {
            if cmp([i, i + 3, i + 6], t) ||
               cmp([i * 3, i * 3 + 1, i * 3 + 2], t)
            {
                return true;
            }
        }
        if cmp([0, 4, 8], t) || cmp([2, 4, 6], t)
        {
            return true;
        }
        false
    }

    fn display(&self) -> &Self
    {
        let mut display_string = String::new();
        for (i, value) in self.status.iter().enumerate()
        {
            let c = match value
            {
                status_type::O     => 'O',
                status_type::X     => 'X',
                status_type::empty => ' ',
            };
            if (i + 1) % 3 == 0
            {
                if i != 8
                {
                    display_string += &format!(" {}\n-----------\n", c).to_string();
                }
                else
                {
                    display_string += &format!(" {}\n", c).to_string();    
                }
            }
            else
            {
                display_string += &format!(" {} |", c).to_string();
            }
        }
        println!("{}", display_string);
        self
    }
}

fn player_step(map: &game_map) -> usize
{
    let mut line = String::new();
    loop
    {
        println!("Please input you step: ");
        std::io::stdin().read_line(&mut line).expect("Did not enter a correct string.");
        match line.trim().parse::<usize>()
        {
            Ok(step)
            if step >= 1 && step <= 9 &&
            map.status[step - 1] == status_type::empty => break step - 1,
            _ => println!("Try again. Enter a correct number in 1-9.")
        }
        line.clear();
    }
}
struct AI
{
    ai_type: status_type
}

impl AI
{
    fn new(t: status_type) -> Self
    {
        AI { ai_type: t }
    }
    
    fn find_max_step(&self, map: &mut game_map) -> usize
    {
        0
    }

    fn find_min_step(&self, map: &mut game_map) -> usize
    {
        0
    }

    fn find_step(&self, map: &mut game_map) -> usize
    {
        0
    }
}

fn main()
{
    let mut time = usize::MIN;
    let ai = AI::new(status_type::X);
    let mut m = game_map::new();

    let mut flag = true;
    let mut step = usize::MIN;
    let mut status = status_type::empty;

    println!("game start!");
    m.display();

    while time <= 8
    {
        if(flag)
        {
            flag = false;
            step = player_step(&m);
            status = status_type::O;
        }
        else
        {
            flag = true;
            // let start = Instant::now();
            // step = ai.find_step(&mut m);
            // println!("time: {}ms", start.elapsed().as_nanos() as f64 / 1000000.0);
            step = ai.find_step(&mut m);
            status = status_type::X;
        }

        m.update(step, status).display();

        if m.is_win(status) { break; }

        status = status_type::empty;
        time += 1;
    };

    m.display();
    println!("{}", match status
    {
        status_type::O     => "You win!",
        status_type::X     => "You failed.",
        status_type::empty => "draw."
    });
}
