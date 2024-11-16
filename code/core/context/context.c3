module context(<Type>);

import keyboard;

fn void exec(Type* ctx)
{
    bool stop = false;

    ctx.init();
	while(stop == false)
	{
		if (keyboard::handler(<Type>)(ctx)) stop = true;
        ctx.update();
	}
}

fn void start()
{
    Type ctx @noinit;
    context::exec(<Type>)(&ctx);
}