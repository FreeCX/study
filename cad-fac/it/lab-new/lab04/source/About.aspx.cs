using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class About : Page
{
    static int image_number = 1;
    static int phrase_number = 1;
    static int counter = 0;
    static Random rnd = new Random();
    string[] phrases = {
        "После всего ада, через который мы прошли, я знаю одно: мы можем положиться "+
        "друг на друга и достигнуть цели, или погибнуть, если такова цена... Потому что есть вещи, "+
        "за которые стоит бороться!",
        "Сомнения — первый шаг на пути к поражению.",
        "Сначала стреляй, потом сомневайся.",
        "Ты мне нравишься. Тебя я убью последним.",
        "Единственное, что ты должен чувствовать, стреляя в кого-то — это отдача.",
        "Огонь снимает с тела кожу, а с души — грех. Огонь выжигает всю грязь, а мама с детства учила меня чистоте.",
        "Ревность — удел слабых духом. Она заполняет сознание распутными мыслями, не оставляя места для остального.",
        "Да мне цены нет! Даже страховку оформить не могу!",
        "Скромность украшает, но оставляет голодным.",
        "«Мы строим — вы отдыхаете». Именно под таким девизом работает союз эльфов-строителей. Вот и отдыхай, и не "+
        "мешай нам строить!",
        "Ты же командир! Не делай умное лицо!",
        "И солнце ярче блещет,<br>И веселей пейзаж,<br>Когда в желудке плещется<br>C2H5OH!",
        "— Скажи-ка, дядя, ведь не даром?<br>— Ну конечно, не даром!",
        "Не могу стоять, пока другие работают... Пойду полежу.",
        "— Рожденный ползать упасть не может!",
        "— Кто к нам с мечем придет, тех проще застрелить!",
        "— Первое условие бессмертия — смерть.",
        "— Быстро и дешево выполню любую халтуру!",
        "— Если смертные достают, то достают до смерти.",
        "— Все не так плохо, как вам кажется. Все намного, намного хуже.",
        "— Я не злопамятный, я запишу.",
        "— И никакие мы не сектанты, мы просто группа ошалелых вооружённых фанатиков!",
        "— Гоблин в доспехах — консервы, завтрак дракона."
    };
    int image_count = 31;
    protected void Page_Load(object sender, EventArgs e)
    {
        Image1.ImageUrl = "images/image_" + image_number + ".jpg";
        Label1.Text = "<b>Быстрая цитата</b><br>" + phrases[phrase_number];
    }
    protected void Timer1_Tick1(object sender, EventArgs e)
    {
        image_number = rnd.Next(1, image_count);
        if ( counter % 2 == 0 ) {
            phrase_number = rnd.Next(1, phrases.Length);
        }
        counter++;
    }
}