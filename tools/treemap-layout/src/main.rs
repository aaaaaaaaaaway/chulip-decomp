//! decomp.dev's streemap::binary layout, with its normalized f32 geometry.
//! Input: aspect ratio followed by function byte sizes. Output: index x y w h.
use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut tokens = input.split_whitespace();
    let aspect: f32 = tokens.next().unwrap().parse().unwrap();
    assert!(aspect.is_finite() && aspect > 0.0);
    let mut items: Vec<_> = tokens
        .enumerate()
        .map(|(index, token)| {
            let size: f32 = token.parse().unwrap();
            assert!(size.is_finite() && size > 0.0);
            (index, size)
        })
        .collect();
    if items.is_empty() {
        return;
    }
    let rect = if aspect > 1.0 {
        streemap::Rect::from_size(1.0, 1.0 / aspect)
    } else {
        streemap::Rect::from_size(aspect, 1.0)
    };
    streemap::binary(
        rect,
        &mut items,
        |item| item.1,
        |item, mut rect| {
            if aspect > 1.0 {
                rect.y *= aspect;
                rect.h *= aspect;
            } else {
                rect.x /= aspect;
                rect.w /= aspect;
            }
            println!("{} {} {} {} {}", item.0, rect.x, rect.y, rect.w, rect.h);
        },
    );
}
