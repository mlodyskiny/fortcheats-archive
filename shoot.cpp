// Original: https://github.com/homeless1337/fortnite-exploits/blob/main/shoot.cpp

float* (*CalcShot)(uintptr_t, uintptr_t, uintptr_t) = nullptr;
float* CalcShotHook(uintptr_t arg0, uintptr_t arg1, uintptr_t arg2) {

	auto ret = SpoofCall(CalcShot, arg0, arg1, arg2);
	auto root = GetPawnRootLocation(LocalPawn);

	SDK::FVector head;
	head.X = AimingActor.x;
	head.Y = AimingActor.y;
	head.Z = AimingActor.z;

	if (ret && bSilent && LocalPawn) {
  
		auto dx = head.X - root.x;
		auto dy = head.Y - root.y;
		auto dz = head.Z - root.z;


		ret[4] = head.X;
		ret[5] = head.Y;
		ret[6] = head.Z;

		head.Z -= 15.0f;

		head.X -= 15.0f;
		head.Y -= 15.0f;

		root.z += 45.0f;

		auto y = atan2f(head.Y - root.y, head.X - root.x);

		root.x += cosf(y + 1.5708f) * 32.0f;
		root.y += sinf(y + 1.5708f) * 32.0f;


		ret[4] = head.X;
		ret[5] = head.Y;
		ret[6] = head.Z;

		auto length = SpoofCall(sqrtf, powf(head.X - root.x, 2) + powf(head.Y - root.y, 2));
		auto x = -atan2f(head.Z - root.z, length);
		y = atan2f(head.Y - root.y, head.X - root.x);

		x /= 2.0f;
		y /= 2.0f;

		ret[0] = -(sinf(x) * sinf(y));
		ret[1] = sinf(x) * cosf(y);
		ret[2] = cosf(x) * sinf(y);
		ret[3] = cosf(x) * cosf(y);
	}

	return ret;
}

void hookthisshit()
{
addr = PatternScan(("48 89 5C 24 ? 4C 89 4C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F9 4C 8D 6C 24 ?"));
	(DiscordHelper::hookint, addr, (uintptr_t)CalcShotHook, (uintptr_t)&CalcShot);
}
